#ifndef RUNESAD_CLIENTSTUB_HPP
#define RUNESAD_CLIENTSTUB_HPP
#define WAIT_FOR_SERVER sf::sleep(sf::seconds(0.0f))

#include "Network/Messages/Base/AllMessages.hpp"
#include "Network/Socket/TslSocket.hpp"
#include <cstring>

class ClientStub
{
public:
    ClientStub();

    void sendAuthenticate(const std::string &username, const std::string &password);
    void receiveAuthenticate(MessageResult res = MessageResult::Ok);
private:
    ssf::TslSocket socket;
    sf::Packet packet;
    /* inne funkcje wysyłające i weryfikujące inne wiadomości */
};

#endif //RUNESAD_CLIENTSTUB_HPP
