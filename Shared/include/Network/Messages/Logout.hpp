#ifndef SADZA_LOGOUT_HPP
#define SADZA_LOGOUT_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"


namespace Msg {
    struct Logout {
        static const MsgType id = MessageType::Logout;
    };
};

sf::Packet &operator<<(sf::Packet &packet, const Msg::Logout &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::Logout &msg);


#endif //SADZA_LOGOUT_HPP
