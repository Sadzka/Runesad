#ifndef SADZA_JOINLOBBY_HPP
#define SADZA_JOINLOBBY_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"
#include <string>
#include <SFML/System/Vector2.hpp>


namespace Msg {
    struct JoinLobby {
        static const MsgType id = MessageType::JoinLobby;
        std::string name;
    };
    struct JoinLobbyResp {
        static const MsgType id = MessageType::JoinLobbyResp;
        MessageResult result;
        std::string mapFile;
        std::string mapName;
    };
}

sf::Packet &operator<<(sf::Packet &packet, const Msg::JoinLobby &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::JoinLobby &msg);

sf::Packet &operator<<(sf::Packet &packet, const Msg::JoinLobbyResp &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::JoinLobbyResp &msg);

#endif //SADZA_JOINLOBBY_HPP
