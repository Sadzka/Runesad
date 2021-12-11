#ifndef SADZA_CONSOLE_HPP
#define SADZA_CONSOLE_HPP

#include <SFML/System/Thread.hpp>
#include <iostream>
#include <sstream>
#include "Console/Command.hpp"
#include "AllCommands.hpp"
#include "Sys/SysLog.hpp"
#include "Server.hpp"

class Console {
public:
    Console(Server & server);
    ~Console();

private:
    std::vector < Command * > commands;
    Server & m_server;
    sf::Thread m_thread;
    bool m_running = true;

    void listenInput();

    void parseLine(const std::string &line);

    void loadCommands();

    void lateLoadCommands();
};


#endif //SADZA_CONSOLE_HPP
