#ifndef RUNESAD_CLIENT_HPP
#define RUNESAD_CLIENT_HPP

#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>
#include <TGUI/Vector2.hpp>
#include <Network/Messages/UpdateUnitInd.hpp>
#include "Network/Socket/TslListener.hpp"

class Client {
public:
    Client();

    void connect();
    void disconnect();
    sf::Uint32 isConnected();

    void sendAuthenticate(const std::string &username, const std::string &password);
    void sendLogout();
    void sendGetLobbyList();
    void sendCreateLobby(const std::string &name);
    void sendJoinLobby(const std::string &name);
    void sendLeaveLobby();
    void sendCloseLobbySlot(sf::Uint8 slot);
    void sendStartLobbyGame();
    void sendShotInd();
    void sendDestroy(unsigned int id);
    void sendDestroyTile(sf::Vector2f position);

    void sendMoveInd(bool b, Direction dir = Direction::None);

private:
    void listenThreadFunction();
    sf::Thread listenThread;
    bool listening = true;

    ssf::TslSocket socket;
};

#endif //RUNESAD_CLIENT_HPP
