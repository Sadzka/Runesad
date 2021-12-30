#include "Network/Messages/DestroyInd.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::DestroyInd &msg) { return packet << msg.entityId; }

sf::Packet &operator>>(sf::Packet &packet, Msg::DestroyInd &msg) { return packet >> msg.entityId; }
