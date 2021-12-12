#ifndef SADZA_AUTHENTICATE_HPP
#define SADZA_AUTHENTICATE_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"
#include <string>

namespace Msg {
    struct Authenticate {
        static const MessageId id = MessageType::Authenticate;
        std::string username;
        std::string password;
    };

    struct AuthenticateResp {
        static const MessageId id = MessageType::AuthenticateResp;
        MessageResult result;
    };
}

sf::Packet& operator <<(sf::Packet& packet, const Msg::Authenticate& msg);
sf::Packet& operator >>(sf::Packet& packet, Msg::Authenticate& msg);

sf::Packet& operator <<(sf::Packet& packet, const Msg::AuthenticateResp& msg);
sf::Packet& operator >>(sf::Packet& packet, Msg::AuthenticateResp& msg);

#endif //SADZA_AUTHENTICATE_HPP
