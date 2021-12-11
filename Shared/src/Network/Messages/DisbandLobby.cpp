#include "Network/Messages/DisbandLobby.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::DisbandLobby &msg) { return packet; }

sf::Packet &operator>>(sf::Packet &packet, Msg::DisbandLobby &msg) { return packet; }
