#ifndef SADZA_STARTLOBBYGAME_HPP
#define SADZA_STARTLOBBYGAME_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"


namespace Msg {
    struct StartLobbyGame {
        static const MsgType id = MessageType::StartLobbyGame;
        sf::Uint32 playerId;
    };
}

sf::Packet &operator<<(sf::Packet &packet, const Msg::StartLobbyGame &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::StartLobbyGame &msg);

#endif //SADZA_STARTLOBBYGAME_HPP
