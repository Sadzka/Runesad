#include <Sys/SysLog.hpp>
#include "Console/Shutdown.hpp"


void Shutdown::setActivators() {
    activators.emplace_back("shutdown");
    activators.emplace_back("exit");
    activators.emplace_back("stop");
}

void Shutdown::callback(Server & server) {
    SysLog::Print(SysLog::Severity::Info, "Shutdown server by command...");
    server.stop();
}

