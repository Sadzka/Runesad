#include <Sys/SysLog.hpp>
#include <SFML/System/Sleep.hpp>
#include <Server.hpp>
#include <Console/Console.hpp>

int main() {
    SysLog logger;
    Server server;
    Console console(server);

    while (server.isRunning()) {
        sf::sleep(sf::milliseconds(33));
    }


    SysLog::Print(SysLog::Severity::Info, "Server successfuly shutdowned.");
    // Wait for all logs.
    sf::sleep(sf::seconds(1));
    return 0;
}
