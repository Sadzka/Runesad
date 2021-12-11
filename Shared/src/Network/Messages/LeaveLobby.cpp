#include "Network/Messages/LeaveLobby.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::LeaveLobby &msg) { return packet; }

sf::Packet &operator>>(sf::Packet &packet, Msg::LeaveLobby &msg) { return packet; }

sf::Packet &operator<<(sf::Packet &packet, const Msg::LeaveLobbyResp &msg) { return packet; }

sf::Packet &operator>>(sf::Packet &packet, Msg::LeaveLobbyResp &msg) { return packet; }
