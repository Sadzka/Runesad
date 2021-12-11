#ifndef SADZA_COMMAND_HPP
#define SADZA_COMMAND_HPP

#include <Server.hpp>

#include <vector>
#include <string>

class Command {

public:
    Command() = default;

    bool invoke(const std::string &str, Server & server);

    void callActivators();

protected:
    std::vector<std::string> activators;

    virtual void setActivators() = 0;

    virtual void callback(Server & server) = 0;
};


#endif //SADZA_COMMAND_HPP
