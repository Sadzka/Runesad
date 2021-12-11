#include <SFML/Network/Socket.hpp>
#include "Network/Client.hpp"
#include "Network/Messages/Base/AllMessages.hpp"
#include "Network/Messages/Base/MsgCreator.hpp"
#include "Base/SharedContext.hpp"

void Client::listenThreadFunction() {
    using namespace Msg;

    socket.setBlocking(false);
    while (listening) {
        sf::Packet packet;
        socket.receive(packet);
        MessageId messageId = GetId(packet);

        switch (messageId) {
            case AuthenticateResp::id: {
                auto msg = Creator<AuthenticateResp::id>::Create(packet);
                printf("Result: %u\n", msg.result);
                StateManager * sm = SharedContext::getStateManager();
                if (sm->getCurrentStateType() == StateType::Main)
                {
                    StateMain *sMain = (StateMain*)(sm->getCurrentState());
                    sMain->cancelAuthenticateInProgress(MessageResult::Ok);
                }
                break;
            }
            default:
            {
                break;
            }
        }
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
