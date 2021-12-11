#ifndef SADZA_HEARTHBEAT_HPP
#define SADZA_HEARTHBEAT_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"
#include <string>

namespace Msg {
    struct Hearthbeat {
        static const MessageId id = MessageType::Hearthbeat;
    };
};

sf::Packet& operator <<(sf::Packet& packet, const Msg::Hearthbeat& msg);
sf::Packet& operator >>(sf::Packet& packet, Msg::Hearthbeat& msg);

#endif //SADZA_HEARTHBEAT_HPP
