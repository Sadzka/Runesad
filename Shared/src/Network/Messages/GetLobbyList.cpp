#include "Network/Messages/GetLobbyList.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::GetLobbyList &msg) { return packet; }

sf::Packet &operator>>(sf::Packet &packet, Msg::GetLobbyList &msg) { return packet; }

sf::Packet &operator<<(sf::Packet &packet, const Msg::GetLobbyListResp &msg) {
    sf::Uint32 x = msg.lobbies.size();
    packet << x;
    for (auto &lobbie : msg.lobbies) {
        packet << lobbie;
    }
    return packet;
}

sf::Packet &operator>>(sf::Packet &packet, Msg::GetLobbyListResp &msg) {
    sf::Uint32 x;
    packet >> x;
    for (int i = 0; i < x; i++)  {
        std::string temp;
        packet >> temp;
        msg.lobbies.push_back(temp);
    }
    return packet;
}
