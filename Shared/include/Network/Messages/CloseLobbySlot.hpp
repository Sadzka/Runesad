#ifndef SADZA_CLOSELOBBYSLOT_HPP
#define SADZA_CLOSELOBBYSLOT_HPP

#include <SFML/Network/Packet.hpp>
#include "Network/Messages/Base/MessageType.hpp"
#include "Network/Messages/Base/MessageResult.hpp"
#include <SFML/Config.hpp>


namespace Msg {
    struct CloseLobbySlot {
        static const MsgType id = MessageType::CloseLobbySlot;
        sf::Uint8 slot;
    };
};

sf::Packet &operator<<(sf::Packet &packet, const Msg::CloseLobbySlot &msg);

sf::Packet &operator>>(sf::Packet &packet, Msg::CloseLobbySlot &msg);

#endif //SADZA_CLOSELOBBYSLOT_HPP
