#ifndef SADZA_MESSAGETYPES_HPP
#define SADZA_MESSAGETYPES_HPP

namespace MessageType {
    enum MessageType : unsigned {
        Hearthbeat          = 0x000000,
        Authenticate        = 0x000001,
        AuthenticateResp    = 0x000002,
        Logout              = 0x000003,
        CreateLobby         = 0x000004,
        CreateLobbyResp     = 0x000005,
        GetLobbyList        = 0x000006,
        GetLobbyListResp    = 0x000007,
        JoinLobby           = 0x000008,
        JoinLobbyResp       = 0x000009,
        LeaveLobby          = 0x00000A,
        LeaveLobbyResp      = 0x00000B,
        DisbandLobby        = 0x00000C,
        UpdateLobbyStatus   = 0x00000D,
        CloseLobbySlot      = 0x00000E,
        StartLobbyGame      = 0x00000F,
        GameEnd             = 0x000010,
        MoveInd             = 0x000011,
        UpdateUnitInd,
        OutOfRange [[maybe_unused]]
    };
}

using MsgType = MessageType::MessageType;
using MessageId = unsigned;

#endif //SADZA_MESSAGETYPES_HPP
