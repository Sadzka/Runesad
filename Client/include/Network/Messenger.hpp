#ifndef RUNESAD_MESSENGER_HPP
#define RUNESAD_MESSENGER_HPP

#include "Network/Messages/Base/AllMessages.hpp"
#include "Network/Messages/Base/MsgCreator.hpp"

class Client;

class Messenger {
public:
    static void handleMessage(Client *client, MessageId id, sf::Packet &packet);
};


#endif //RUNESAD_MESSENGER_HPP
