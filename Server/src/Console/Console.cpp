#include "Console/Console.hpp"

Console::Console(Server & server) : m_server(server), m_thread(listenInput, this) {
    loadCommands();
    m_thread.launch();
}

Console::~Console() {
    for (Command *command : commands) {
        delete command;
    }
    m_thread.terminate();
}

void Console::listenInput() {
    std::string line;

    while (m_running) {
        std::getline(std::cin, line);
        parseLine(line);
    }
}

void Console::parseLine(const std::string & line) {
    std::stringstream ss(line);
    std::string commandName;
    ss >> commandName;

    SysLog::Print(SysLog::Severity::ConsoleIn, "%s", ss.str().c_str());
    for (Command * command : commands) {
        if (command->invoke(commandName, m_server)) { return; }
    }

    SysLog::Print(SysLog::Severity::Console, "%s: command not found", commandName.c_str());
}

void Console::loadCommands() {
    commands.emplace_back(new Shutdown());
    lateLoadCommands();
}

void Console::lateLoadCommands() {
    for (Command *command : commands) {
        command->callActivators();
    }
}
