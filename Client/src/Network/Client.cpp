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
    file.open("data/maps/" + filename, std::ios::in);
    if (!file.good()) throw std::runtime_error("Error in opening file");
    std::string line;
    while(getline(file, line))
    {
        msg.mapFile += line + '\n';
    }
    file.close();

    msg.mapName = filename;
    Messenger::mapFile = filename;

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
    Msg::CloseLobbySlot msg{};
    msg.slot = slot;
    socket.send(msg);
}
void Client::sendStartLobbyGame() {
    Msg::StartLobbyGame msg{};
    socket.send(msg);
}

void Client::sendShotInd() {
    Msg::ShotInd msg{};
    StateGame *state = (StateGame*)(SharedContext::getStateManager()->getCurrentState());
    auto optEntity = SharedContext::getEntityManager()->getEntity(state->getPlayerId());
    if (optEntity.has_value())
    {
        msg.position = optEntity.value()->getPosition();
        msg.direction = static_cast<sf::Uint8>(optEntity.value()->getDirection());
    }
    socket.send(msg);
}

void Client::sendDestroy(unsigned int id) {
    Msg::DestroyInd ind{};
    ind.entityId = id;
    socket.send(ind);
}

void Client::sendDestroyTile(sf::Vector2f position) {
    Msg::DestroyTileInd ind{};
    ind.position.x = position.x/32;
    ind.position.y = position.y/32;
    socket.send(ind);
}

void Client::sendMoveInd(bool b, Direction dir) {

    Msg::MoveInd ind{};
    StateGame *state = (StateGame*)(SharedContext::getStateManager()->getCurrentState());

    ind.unitId = state->getPlayerId();
    ind.start = b;
    ind.direction = static_cast<sf::Uint8>(dir);
    socket.send(ind);
}
