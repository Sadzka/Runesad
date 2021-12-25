#include "Network/Messages/StartLobbyGame.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::StartLobbyGame &msg) { return packet << msg.playerId; }

sf::Packet &operator>>(sf::Packet &packet, Msg::StartLobbyGame &msg) { return packet >> msg.playerId; }
