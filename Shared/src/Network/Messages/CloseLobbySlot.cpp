#include "Network/Messages/CloseLobbySlot.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::CloseLobbySlot &msg) { return packet << msg.slot; }

sf::Packet &operator>>(sf::Packet &packet, Msg::CloseLobbySlot &msg) { return packet >> msg.slot; }
