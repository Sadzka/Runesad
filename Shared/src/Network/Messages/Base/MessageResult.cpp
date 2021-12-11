#include "Network/Messages/Base/MessageResult.hpp"

sf::Packet &operator<<(sf::Packet &packet, const MessageResult &msg) { return packet << (unsigned) (msg); }

sf::Packet &operator>>(sf::Packet &packet, MessageResult &msg) {
    unsigned i;
    packet >> i;
    msg = MessageResult(i);
    return packet;
}