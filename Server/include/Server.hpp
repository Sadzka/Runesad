#ifndef SADZA_CLIENT_SERVER_HPP
#define SADZA_CLIENT_SERVER_HPP

#include <SFML/System/Sleep.hpp>

#include "Network/Messages/Base/MsgCreator.hpp"
#include "Network/Socket/TslListener.hpp"
#include "Config/ConfigLoader.hpp"
#include <SFML/Network.hpp>
#include "Utils/Sha512.hpp"

#include <Sys/SysLog.hpp>
#include "Client.hpp"
#include "Games.hpp"

#define SERVER_PORT 1111

class Server {
    friend class Messenger;
public:
    Server();

    ~Server();

    [[nodiscard]] bool isRunning() const;

    void stop();

private:

    void authenticateThreadFunction();

    void listenThreadFunction();

    void processGames();

    std::unordered_map <sf::Uint64, std::shared_ptr<Client>> clients;
    std::vector <sf::Uint64> timeoutList;
    sf::Thread listenThread;
    sf::Thread authenticateThread;
    bool running = true;
    ConfigData cfg;
    sf::Mutex mutex;
    SHA256_CTX context;
    sf::Clock clock;
    sf::Uint64 nextClientId = 0;

    Games games;
};


#endif //SADZA_CLIENT_SERVER_HPP
