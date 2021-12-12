#include "Network/Messages/JoinLobby.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::JoinLobby &msg) { return packet << msg.name; }

sf::Packet &operator>>(sf::Packet &packet, Msg::JoinLobby &msg) { return packet >> msg.name; }

sf::Packet &operator<<(sf::Packet &packet, const Msg::JoinLobbyResp &msg) { return packet << msg.result << msg.mapFile << msg.mapName; }

sf::Packet &operator>>(sf::Packet &packet, Msg::JoinLobbyResp &msg) { return packet >> msg.result >> msg.mapFile >> msg.mapName; }
