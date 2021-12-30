#ifndef SADZA_SHOTIND_HPP
#define SADZA_SHOTIND_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"
#include <SFML/System/Vector2.hpp>


namespace Msg {
    struct ShotInd {
        static const MsgType id = MessageType::ShotInd;
        sf::Vector2f position;
        sf::Uint8 direction;
    };
}

sf::Packet &operator<<(sf::Packet &packet, const Msg::ShotInd &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::ShotInd &msg);

#endif //SADZA_SHOTIND_HPP
