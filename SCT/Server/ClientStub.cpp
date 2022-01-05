#include "ClientStub.hpp"

#include <cassert>
#include <SFML/System/Sleep.hpp>
#include <SFML/Network.hpp>
#include "Network/Messages/Base/MsgCreator.hpp"

using namespace Msg;

ClientStub::ClientStub() : socket(ssf::SocketSide::Client) {
    ssf::Socket::Status result = socket.connect("localhost", 1111);
    assert (result == ssf::Socket::Status::Done);

    socket.setBlocking(true);
}
void ClientStub::sendAuthenticate(const std::string &username, const std::string &password) {
    Msg::Authenticate msg{};
    msg.username = username;
    msg.password = password;
    socket.send(msg);
}

void ClientStub::receiveAuthenticate(MessageResult res) {
    assert(socket.receive(packet) == ssf::Socket::Done);

    MessageId messageId = GetId(packet);
    AuthenticateResp msg{};
    packet >> msg;

    assert(messageId == AuthenticateResp::id);
    assert(msg.result == res);
}