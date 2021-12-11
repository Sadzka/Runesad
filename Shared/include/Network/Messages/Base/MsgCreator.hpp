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
                Msg::Hearthbeat msg{};
                packet >> msg;
                return msg;
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

        template <unsigned DUMMY>
        struct Loop<MsgType::Logout, DUMMY> {
            static auto execute(sf::Packet & packet) {
                Msg::Hearthbeat msg{};
                packet >> msg;
                return msg;
            }
        };
        template <unsigned DUMMY>
        struct Loop<MsgType::CloseLobbySlot, DUMMY> {
            static auto execute(sf::Packet & packet) {
                Msg::CloseLobbySlot msg{};
                packet >> msg;
                return msg;
            }
        };
        template <unsigned DUMMY>
        struct Loop<MsgType::CreateLobby, DUMMY> {
            static auto execute(sf::Packet & packet) {
                Msg::CreateLobby msg{};
                packet >> msg;
                return msg;
            }
        };
        template <unsigned DUMMY>
        struct Loop<MsgType::DisbandLobby, DUMMY> {
            static auto execute(sf::Packet & packet) {
                Msg::DisbandLobby msg{};
                packet >> msg;
                return msg;
            }
        };
        template <unsigned DUMMY>
        struct Loop<MsgType::GetLobbyList, DUMMY> {
            static auto execute(sf::Packet & packet) {
                Msg::DisbandLobby msg{};
                packet >> msg;
                return msg;
            }
        };
        template <unsigned DUMMY>
        struct Loop<MsgType::GetLobbyListResp, DUMMY> {
            static auto execute(sf::Packet & packet) {
                Msg::GetLobbyListResp msg{};
                packet >> msg;
                return msg;
            }
        };
        template <unsigned DUMMY>
        struct Loop<MsgType::JoinLobby, DUMMY> {
            static auto execute(sf::Packet & packet) {
                Msg::JoinLobby msg{};
                packet >> msg;
                return msg;
            }
        };
        template <unsigned DUMMY>
        struct Loop<MsgType::LeaveLobby, DUMMY> {
            static auto execute(sf::Packet & packet) {
                Msg::LeaveLobby msg{};
                packet >> msg;
                return msg;
            }
        };
        template <unsigned DUMMY>
        struct Loop<MsgType::LeaveLobbyResp, DUMMY> {
            static auto execute(sf::Packet & packet) {
                Msg::LeaveLobbyResp msg{};
                packet >> msg;
                return msg;
            }
        };
        template <unsigned DUMMY>
        struct Loop<MsgType::StartLobbyGame, DUMMY> {
            static auto execute(sf::Packet & packet) {
                Msg::LeaveLobbyResp msg{};
                packet >> msg;
                return msg;
            }
        };
        template <unsigned DUMMY>
        struct Loop<MsgType::UpdateLobbyStatus, DUMMY> {
            static auto execute(sf::Packet & packet) {
                Msg::LeaveLobbyResp msg{};
                packet >> msg;
                return msg;
            }
        };
    };
};

#endif //SADZA_MSGCREATOR_HPP
        