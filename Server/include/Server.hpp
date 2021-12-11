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

#define SERVER_PORT 1111

class Server {
public:
    Server();

    ~Server();

    [[nodiscard]] bool isRunning() const;

    void stop();

private:

    void authenticateThreadFunction();

    void listenThreadFunction();

    std::unordered_map <std::string, std::shared_ptr<Client>> clients;
    sf::Thread listenThread;
    sf::Thread authenticateThread;
    bool running = true;
    ConfigData cfg;
    sf::Mutex mutex;
    SHA256_CTX context;
    sf::Clock clock;
};


#endif //SADZA_CLIENT_SERVER_HPP
