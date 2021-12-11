#ifndef RUNESAD_CLIENT_HPP
#define RUNESAD_CLIENT_HPP

struct Client
{
    ssf::TslSocket socket;
    std::string username;
    sf::Uint64 hearthbeat;

    Client() : socket(ssf::SocketSide::Server) {}

};

#endif //RUNESAD_CLIENT_HPP
