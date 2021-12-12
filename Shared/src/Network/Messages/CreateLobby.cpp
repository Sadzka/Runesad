#include "Network/Messages/CreateLobby.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::CreateLobby &msg) {
    return packet << msg.name << msg.mapName << msg.mapFile;
}

sf::Packet &operator>>(sf::Packet &packet, Msg::CreateLobby &msg) {
    return packet >> msg.name >> msg.mapName >> msg.mapFile;
}

sf::Packet &operator<<(sf::Packet &packet, const Msg::CreateLobbyResp &msg) { return packet  << msg.result; }

sf::Packet &operator>>(sf::Packet &packet, Msg::CreateLobbyResp &msg) { return packet  >> msg.result; }
