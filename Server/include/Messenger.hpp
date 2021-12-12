#ifndef RUNESAD_MESSENGER_HPP
#define RUNESAD_MESSENGER_HPP
#include <SFML/Network.hpp>
#include "Server.hpp"

class Messenger
{
public:
    static void handleMessage(Server *server, std::shared_ptr<Client> &client, sf::Uint64 clientId, MessageId id, sf::Packet &packet);
};

#endif //RUNESAD_MESSENGER_HPP
