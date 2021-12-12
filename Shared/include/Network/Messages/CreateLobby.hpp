#ifndef SADZA_CREATELOBBY_HPP
#define SADZA_CREATELOBBY_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"
#include <string>
#include <SFML/System/Vector2.hpp>


namespace Msg {
    struct CreateLobby {
        static const MsgType id = MessageType::CreateLobby;
        std::string name;
        std::string mapName;
        std::string mapFile;
    };
    struct CreateLobbyResp {
        static const MsgType id = MessageType::CreateLobbyResp;
        MessageResult result;
    };
}

sf::Packet &operator<<(sf::Packet &packet, const Msg::CreateLobby &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::CreateLobby &msg);

sf::Packet &operator<<(sf::Packet &packet, const Msg::CreateLobbyResp &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::CreateLobbyResp &msg);

#endif //SADZA_CREATELOBBY_HPP
