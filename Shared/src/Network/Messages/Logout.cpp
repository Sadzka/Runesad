#include "Network/Messages/Logout.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::Logout &msg) { return packet; }

sf::Packet &operator>>(sf::Packet &packet, Msg::Logout &msg) { return packet; }
