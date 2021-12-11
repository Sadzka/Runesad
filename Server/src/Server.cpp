#include "Server.hpp"
#include "Database/Database.hpp"
#include "Messenger.hpp"

Server::Server() :
            authenticateThread(&Server::authenticateThreadFunction, this),
            listenThread(&Server::listenThreadFunction, this) {

    if (!SHA256_Init(&context))
        return;

    ConfigLoader cfgLoader("Config/Server.cfg", cfg);

    authenticateThread.launch();
    listenThread.launch();
}

Server::~Server() {
    authenticateThread.terminate();
    listenThread.terminate();
}

bool Server::isRunning() const {
    return running;
}

void Server::stop() {
    running = false;
}

void Server::authenticateThreadFunction() {
    ssf::TslListener listener;
    if (listener.listen(SERVER_PORT) != ssf::Socket::Done) {
        SysLog::Print(SysLog::Severity::Error, "[Authenticate Thread] listen() error.");
        running = false;
    }
    SysLog::Print(SysLog::Severity::Info, "[Authenticate Thread] start listening.");

    while (running) {
        std::shared_ptr<Client> client = std::make_shared<Client>();
        if (listener.accept(client->socket) != ssf::Socket::Done) {
            SysLog::Print(SysLog::Severity::Error, "[Authenticate Thread] accept() error.");
            running = false;
        }
        SysLog::Print(SysLog::Severity::Info, "[Authenticate Thread] New connection from %s:%u",
                      client->socket.getRemoteAddress().toString().c_str(), client->socket.getRemotePort());

        client->hearthbeat = clock.getElapsedTime().asMicroseconds();
        client->socket.setBlocking(false);

        mutex.lock();
        clients.emplace(client->username, client);
        mutex.unlock();
    }
}

void Server::listenThreadFunction()
{
    while (running)
    {
        for (auto &pair : clients) {

            sf::Packet packet;
            std::shared_ptr<Client> &client = pair.second;
            if (client->socket.receive(packet) != ssf::Socket::Done) {
                continue;
            }
            SysLog::Print(SysLog::Severity::Info, "Handle %s", pair.first.c_str());

            MessageId id = Msg::GetId(packet);

            SysLog::Print(SysLog::Severity::Info, "Received msgId=%u", id);
            if (id == MsgType::Authenticate) {

                unsigned char md[SHA256_DIGEST_LENGTH];
                auto msg = Msg::Creator<MsgType::Authenticate>::Create(packet);

                if (!SHA256_Update(&context, msg.password.c_str(), msg.password.length()))
                    return;

                if (!SHA256_Final(md, &context))
                    return;

                std::stringstream ss;
                for (unsigned char i : md) {
                    ss << std::hex << std::setw(2) << std::setfill('0') << (int) i;
                }
                msg.password = ss.str();

                SysLog::Print(SysLog::Severity::Info, "[Authenticate Thread] Authentication request from %s:%u [%s]",
                              client->socket.getRemoteAddress().toString().c_str(),
                              client->socket.getRemotePort(),
                              msg.username.c_str());

                Msg::AuthenticateResp resp{};
                if (clients.find(client->username) != clients.end()) // userAlreadyLogged
                {
                    SysLog::Print(SysLog::Severity::Info, "[Authenticate Thread] Result (%s): Already Logged",
                                  msg.username.c_str());
                    resp.result = MessageResult::AlreadyLogged;
                    client->socket.send(resp);
                    continue;
                }

                if (Database::userExist(msg.username, msg.password))
                {
                    SysLog::Print(SysLog::Severity::Info, "[Authenticate Thread] Result (%s): Ok",
                                  msg.username.c_str());
                    resp.result = MessageResult::Ok;
                }
                else
                {
                    SysLog::Print(SysLog::Severity::Info, "[Authenticate Thread] Result (%s): Ok",
                                  msg.username.c_str());
                    resp.result = MessageResult::InvalidUsernameOrPassword;
                }

                client->socket.send(resp);
                continue;
            }
            else if (id == MsgType::Hearthbeat)
            {
                client->hearthbeat = clock.getElapsedTime().asMicroseconds();
                continue;
            }
            Messenger::handleMessage(this, id, packet);
        }
    }
}