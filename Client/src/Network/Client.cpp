#include <SFML/Network/Socket.hpp>
#include "Network/Client.hpp"
#include "Network/Messages/Base/AllMessages.hpp"
#include "Network/Messages/Base/MsgCreator.hpp"
#include "Base/SharedContext.hpp"
#include "Network/Messenger.hpp"
#include <fstream>

void Client::listenThreadFunction() {
    using namespace Msg;

    socket.setBlocking(false);
    while (listening) {
        sf::Packet packet;
        if (socket.receive(packet) != ssf::Socket::Done) {
            continue;
        }
        MessageId messageId = GetId(packet);

        Messenger::handleMessage(this, messageId, packet);
    }
}

Client::Client() : listenThread(&listenThreadFunction, this),
                   socket(ssf::SocketSide::Client) {
}

void Client::connect() {
    ssf::Socket::Status result = socket.connect("localhost", 1111);
    if (result == ssf::Socket::Status::Done) {
        listenThread.launch();
    }
}

void Client::disconnect() {
    listenThread.terminate();
    socket.disconnect();
}

sf::Uint32 Client::isConnected() { return socket.getRemoteAddress().toInteger(); }

void Client::sendAuthenticate(const std::string &username, const std::string &password) {
    Msg::Authenticate msg;
    msg.username = username;
    msg.password = password;
    socket.send(msg);
}
void Client::sendLogout() {
    Msg::Logout msg;
    socket.send(msg);
}
void Client::sendCreateLobby(const std::string &name) {
    Msg::CreateLobby msg;
    msg.name = name;

    std::string filename = SharedContext::getGui()->get<tgui::Label>("mapNameLabel")->getText().toStdString();
    std::fstream file;
    file.open("Data/maps/" + filename, std::ios::in);
    if (file.good()) throw std::runtime_error("Error in createing file");
    std::string line;
    while(getline(file, line))
    {
        msg.mapFile += line + '\n';
    }
    file.close();

    msg.mapName = filename;

    socket.send(msg);
}
void Client::sendGetLobbyList() {
    Msg::GetLobbyList msg;
    socket.send(msg);
}
void Client::sendJoinLobby(const std::string &name) {
    Msg::JoinLobby msg;
    msg.name = name;
    socket.send(msg);
}
void Client::sendLeaveLobby() {
    Msg::LeaveLobby msg;
    socket.send(msg);
}
void Client::sendCloseLobbySlot(sf::Uint8 slot) {
    Msg::CloseLobbySlot msg;
    msg.slot = slot;
    socket.send(msg);
}
void Client::sendStartLobbyGame() {
    Msg::StartLobbyGame msg;
    socket.send(msg);
}
