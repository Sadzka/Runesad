#ifndef SADZA_MESSAGETYPES_HPP
#define SADZA_MESSAGETYPES_HPP

namespace MessageType {
    enum MessageType : unsigned {
        Hearthbeat = 0,
        Authenticate = 1,
        AuthenticateResp,
        Logout,
        CreateLobby,
        CreateLobbyResp,
        GetLobbyList,
        GetLobbyListResp,
        JoinLobby,
        LeaveLobby,
        LeaveLobbyResp,
        DisbandLobby,
        UpdateLobbyStatus,
        CloseLobbySlot,
        StartLobbyGame,
        OutOfRange [[maybe_unused]]
    };
}

using MsgType = MessageType::MessageType;
using MessageId = unsigned;

#endif //SADZA_MESSAGETYPES_HPP
