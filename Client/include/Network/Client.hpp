#ifndef RUNESAD_CLIENT_HPP
#define RUNESAD_CLIENT_HPP

#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>
#include "Network/Socket/TslListener.hpp"

class Client {
public:
    Client();

    void connect();
    void disconnect();
    sf::Uint32 isConnected();

    void sendAuthenticate(const std::string &username, const std::string &password);
    void sendLogout();
private:
    void listenThreadFunction();
    sf::Thread listenThread;
    bool listening = true;

    ssf::TslSocket socket;
    ssf::TslListener listener;
    sf::Mutex mutex;
};

#endif //RUNESAD_CLIENT_HPP
