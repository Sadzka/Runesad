#ifndef SADZA_GAMEEND_HPP
#define SADZA_GAMEEND_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"
#include <SFML/Config.hpp>

namespace Msg {
    struct GameEnd {
        static const MsgType id = MessageType::GameEnd;
        sf::Uint8 victoriousTeamNumber;
    };
}

sf::Packet &operator<<(sf::Packet &packet, const Msg::GameEnd &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::GameEnd &msg);

#endif //SADZA_GAMEEND_HPP
