#ifndef SADZA_ENDGAMEIND_HPP
#define SADZA_ENDGAMEIND_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"
#include <SFML/Config.hpp>


namespace Msg {
    struct EndGameInd {
        static const MsgType id = MessageType::EndGameInd;
        sf::Uint8 victory;
    };
}

sf::Packet &operator<<(sf::Packet &packet, const Msg::EndGameInd &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::EndGameInd &msg);

#endif //SADZA_ENDGAMEIND_HPP
