#include "Network/Messages/MoveInd.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::MoveInd &msg) { return packet << msg.direction << msg.start << msg.unitId; }

sf::Packet &operator>>(sf::Packet &packet, Msg::MoveInd &msg) { return packet >> msg.direction >> msg.start >> msg.unitId; }
