#ifndef SADZA_LEAVELOBBY_HPP
#define SADZA_LEAVELOBBY_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"


namespace Msg {
    struct LeaveLobby {
        static const MsgType id = MessageType::LeaveLobby;
    };
    struct LeaveLobbyResp {
        static const MsgType id = MessageType::LeaveLobbyResp;
    };
}

sf::Packet &operator<<(sf::Packet &packet, const Msg::LeaveLobby &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::LeaveLobby &msg);

sf::Packet &operator<<(sf::Packet &packet, const Msg::LeaveLobbyResp &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::LeaveLobbyResp &msg);

#endif //SADZA_LEAVELOBBY_HPP
