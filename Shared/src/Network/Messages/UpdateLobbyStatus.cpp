#include "Network/Messages/UpdateLobbyStatus.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::UpdateLobbyStatus &msg) {
    for (int i = 0; i < 8; ++i) {
        packet << msg.open[i] << msg.playerName[i];
    }
    return packet;
}

sf::Packet &operator>>(sf::Packet &packet, Msg::UpdateLobbyStatus &msg) {
    for (int i = 0; i < 8; ++i) {
        packet >> msg.open[i] >> msg.playerName[i];
    }
    return packet;
}
