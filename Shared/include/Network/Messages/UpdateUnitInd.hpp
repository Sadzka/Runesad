#ifndef SADZA_UPDATEUNITIND_HPP
#define SADZA_UPDATEUNITIND_HPP

#include <SFML/Network/Packet.hpp>
#include "SFML/System/Vector2.hpp"
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"
#include <SFML/Config.hpp>

enum class Direction : sf::Uint8 {
    Up = 0,
    Right = 1,
    Down = 2,
    Left = 3,
    None = 255
};

namespace Msg {
    struct UpdateUnitInd {
        static const MsgType id = MessageType::UpdateUnitInd;
        sf::Uint32 unitId;
        sf::Uint8 type;
        sf::Vector2f position;
        Direction direction;
        bool destroy;
    };
}

sf::Packet &operator<<(sf::Packet &packet, const Direction &msg);

sf::Packet &operator>>(sf::Packet &packet, Direction &msg);

sf::Packet &operator<<(sf::Packet &packet, const Msg::UpdateUnitInd &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::UpdateUnitInd &msg);

#endif //SADZA_UPDATEUNITIND_HPP
