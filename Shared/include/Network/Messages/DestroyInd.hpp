#ifndef SADZA_DESTROYIND_HPP
#define SADZA_DESTROYIND_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"
#include <SFML/Config.hpp>


namespace Msg {
    struct DestroyInd {
        static const MsgType id = MessageType::DestroyInd;
        sf::Uint32 entityId;
    };
}

sf::Packet &operator<<(sf::Packet &packet, const Msg::DestroyInd &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::DestroyInd &msg);

#endif //SADZA_DESTROYIND_HPP
