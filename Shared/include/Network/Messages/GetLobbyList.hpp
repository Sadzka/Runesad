#ifndef SADZA_GETLOBBYLIST_HPP
#define SADZA_GETLOBBYLIST_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"


namespace Msg {
    struct GetLobbyList {
        static const MsgType id = MessageType::GetLobbyList;

    };
    struct GetLobbyListResp {
        static const MsgType id = MessageType::GetLobbyListResp;
        std::vector < std::string > lobbies;
    };
};

sf::Packet &operator<<(sf::Packet &packet, const Msg::GetLobbyList &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::GetLobbyList &msg);

sf::Packet &operator<<(sf::Packet &packet, const Msg::GetLobbyListResp &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::GetLobbyListResp &msg);

#endif //SADZA_GETLOBBYLIST_HPP
