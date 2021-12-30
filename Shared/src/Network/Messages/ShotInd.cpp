#include "Network/Messages/ShotInd.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::ShotInd &msg) { return packet << msg.position.x << msg.position.y << msg.direction; }

sf::Packet &operator>>(sf::Packet &packet, Msg::ShotInd &msg) { return packet >> msg.position.x >> msg.position.y >> msg.direction; }
