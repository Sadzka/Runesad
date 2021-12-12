#ifndef SADZA_UPDATELOBBYSTATUS_HPP
#define SADZA_UPDATELOBBYSTATUS_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"
#include <string>
#include <SFML/Config.hpp>


namespace Msg {
    struct UpdateLobbyStatus {
        static const MsgType id = MessageType::UpdateLobbyStatus;
        sf::Uint8 open[8];
        std::string playerName[8];
    };
}

sf::Packet &operator<<(sf::Packet &packet, const Msg::UpdateLobbyStatus &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::UpdateLobbyStatus &msg);

#endif //SADZA_UPDATELOBBYSTATUS_HPP
