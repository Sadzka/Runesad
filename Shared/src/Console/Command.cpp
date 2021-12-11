#include "Console/Command.hpp"


void Command::callActivators() {
    setActivators();
}

bool Command::invoke(const std::string &str, Server & server) {
    for (const std::string &activator : activators) {
        if (str == activator) {
            callback(server);
            return true;
        }
    }
    return false;
}

