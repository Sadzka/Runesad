#include "Network/Messages/Authenticate.hpp"

sf::Packet& operator <<(sf::Packet& packet, const Msg::Authenticate& msg) { return packet << msg.username << msg.password; }

sf::Packet& operator >>(sf::Packet& packet, Msg::Authenticate& msg) { return packet >> msg.username >> msg.password; }

sf::Packet& operator <<(sf::Packet& packet, const Msg::AuthenticateResp& msg) { return packet << msg.result; }

sf::Packet& operator >>(sf::Packet& packet, Msg::AuthenticateResp& msg) { return packet >> msg.result; }
