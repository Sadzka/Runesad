#include "Network/Messages/UpdateUnitInd.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::UpdateUnitInd &msg) {
    return packet << msg.unitId << msg.type << msg.position.x << msg.position.y << msg.direction << msg.destroy;
}

sf::Packet &operator>>(sf::Packet &packet, Msg::UpdateUnitInd &msg) {
    return packet >> msg.unitId >> msg.type >> msg.position.x >> msg.position.y >> msg.direction >> msg.destroy;
}

sf::Packet &operator<<(sf::Packet &packet, const Direction &msg) {
    return packet << sf::Uint8(msg);
}

sf::Packet &operator>>(sf::Packet &packet, Direction &msg) {
    sf::Uint8 dir;
    packet >> dir;
    msg = Direction(dir);
    return packet;
}
