#ifndef SADZA_SHUTDOWN_HPP
#define SADZA_SHUTDOWN_HPP

#include "Console/Command.hpp"

class Shutdown : public Command {
//    Shutdown() = default;
private:
    void setActivators() override;
    void callback(Server & server) override;
};


#endif //SADZA_SHUTDOWN_HPP
