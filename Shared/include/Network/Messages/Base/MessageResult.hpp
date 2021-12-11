#ifndef RUNESAD_MESSAGERESULT_HPP
#define RUNESAD_MESSAGERESULT_HPP

#include <SFML/Network/Packet.hpp>

enum class MessageResult : unsigned {
    Ok = 0,
    InvalidUsernameOrPassword,
    AlreadyLogged,
    InvalidUsername,
    InvalidPassword,
    UnknownStatus
};

sf::Packet &operator<<(sf::Packet &packet, const MessageResult &msg);

sf::Packet &operator>>(sf::Packet &packet, MessageResult &msg);

#endif //RUNESAD_MESSAGERESULT_HPP
