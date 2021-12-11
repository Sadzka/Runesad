#ifndef SADZA_DISBANDLOBBY_HPP
#define SADZA_DISBANDLOBBY_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"


namespace Msg {
    struct DisbandLobby {
        static const MsgType id = MessageType::DisbandLobby;
    };
};

sf::Packet &operator<<(sf::Packet &packet, const Msg::DisbandLobby &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::DisbandLobby &msg);

#endif //SADZA_DISBANDLOBBY_HPP
