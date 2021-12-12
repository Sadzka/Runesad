#ifndef SADZA_MOVEIND_HPP
#define SADZA_MOVEIND_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"
#include <SFML/Config.hpp>


namespace Msg {
    struct MoveInd {
        static const MsgType id = MessageType::MoveInd;
        sf::Uint8 direction;
        bool start;
    };
}

sf::Packet &operator<<(sf::Packet &packet, const Msg::MoveInd &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::MoveInd &msg);

#endif //SADZA_MOVEIND_HPP
