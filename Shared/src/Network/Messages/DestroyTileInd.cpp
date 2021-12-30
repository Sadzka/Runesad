#include "Network/Messages/DestroyTileInd.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::DestroyTileInd &msg) { return packet << msg.position.x << msg.position.y; }

sf::Packet &operator>>(sf::Packet &packet, Msg::DestroyTileInd &msg) { return packet >> msg.position.x >> msg.position.y; }
