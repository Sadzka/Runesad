#include "Network/Messages/GameEnd.hpp"

sf::Packet &operator<<(sf::Packet &packet, const Msg::GameEnd &msg) { return packet << msg.victoriousTeamNumber; }

sf::Packet &operator>>(sf::Packet &packet, Msg::GameEnd &msg) { return packet >> msg.victoriousTeamNumber; }
