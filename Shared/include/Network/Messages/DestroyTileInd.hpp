#ifndef SADZA_DESTROYTILEIND_HPP
#define SADZA_DESTROYTILEIND_HPP

#include <SFML/Network/Packet.hpp>
#include <SFML/System/Vector2.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"


namespace Msg {
    struct DestroyTileInd {
        static const MsgType id = MessageType::DestroyTileInd;
        sf::Vector2f position;
    };
}

sf::Packet &operator<<(sf::Packet &packet, const Msg::DestroyTileInd &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::DestroyTileInd &msg);

#endif //SADZA_DESTROYTILEIND_HPP
