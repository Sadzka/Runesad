#ifndef SADZA_MSGCREATOR_HPP
#define SADZA_MSGCREATOR_HPP

#include "AllMessages.hpp"
#include <SFML/Network/Packet.hpp>

namespace Msg {
    [[nodiscard]] int GetId(sf::Packet & packet);

    template <unsigned N>
    class Creator {
    public:
        Creator() = delete;

        static auto Create(sf::Packet & packet) {
            return Loop<N, 0>::execute(packet);
        };

        template <unsigned M, unsigned DUMMY>
        struct Loop {
            static auto execute(sf::Packet & packet) {
                return Loop<M, 0>::execute(packet);
            }
        };

        template <unsigned DUMMY>
        struct Loop<MsgType::Hearthbeat, DUMMY> {
            static auto execute(sf::Packet & packet) {
//                Msg::Hearthbeat msg{};
//                packet >> msg;
//                return msg;
                return 2;
            }
        };

        template <unsigned DUMMY>
        struct Loop<MsgType::Authenticate, DUMMY> {
            static auto execute(sf::Packet & packet) {
                Msg::Authenticate msg{};
                packet >> msg;
                return msg;
            }
        };

        template <unsigned DUMMY>
        struct Loop<MsgType::AuthenticateResp, DUMMY> {
            static auto execute(sf::Packet & packet) {
                Msg::AuthenticateResp msg{};
                packet >> msg;
                return msg;
            }
        };
    };
};

#endif //SADZA_MSGCREATOR_HPP
        