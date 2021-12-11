#ifndef RUNESAD_CLIENT_HPP
#define RUNESAD_CLIENT_HPP
#include "Network/Socket/TslSocket.hpp"

class Lobby;

enum class ClientStatus
{
    Idle = 0,
    InLobby = 1,
    InGame = 2
};

struct Client
{
    ClientStatus status = ClientStatus::Idle;
    ssf::TslSocket socket;
    std::string username = "";
    sf::Uint64 hearthbeat = 0;
    Lobby * lobby;
    bool authenticated = false;

    Client() : socket(ssf::SocketSide::Server) {}
    ~Client() { socket.disconnect(); }

    template <class T>
    void send(T &t) {
        socket.send(t);
    }
};

#endif //RUNESAD_CLIENT_HPP
