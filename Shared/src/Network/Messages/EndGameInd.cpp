#include "Network/Messages/EndGameInd.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::EndGameInd &msg) { return packet << msg.victory; }

sf::Packet &operator>>(sf::Packet &packet, Msg::EndGameInd &msg) { return packet >> msg.victory; }
