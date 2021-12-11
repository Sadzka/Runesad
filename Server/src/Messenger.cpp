#include "Messenger.hpp"

void Messenger::handleMessage(Server *server, std::shared_ptr<Client> &client, MessageId id, sf::Packet &packet)
{
    using namespace Msg;
    Games *games = &server->games;

    switch (id) {
        case MsgType::Logout:
        {
            SysLog::Print(SysLog::Severity::Info, "[%s] Logout",
                          client->username.c_str());
            server->timeoutList.push_back(client->username);
            break;
        }
        case MsgType::CreateLobby:
        {
            CreateLobby msg;
            packet >> msg;
            SysLog::Print(SysLog::Severity::Info, "[%s] CreateLobby - %s",
                          client->username.c_str(), msg.name.c_str());
            server->games.createLobby(client, msg.name);
            client->status = ClientStatus::InLobby;
            break;
        }
        case MsgType::GetLobbyList:
        {
            GetLobbyListResp resp;
            resp.lobbies = games->getLobbyList();

            client->send(resp);
        }
        case MsgType::JoinLobby:
        {
            Lobby *lobby = client->lobby;
            JoinLobby req;
            packet >> req;

            JoinLobbyResp resp{};
            if (games->joinLobby(client, req.name)) {
                resp.result = MessageResult::Ok;
            }
            else {
                resp.result = MessageResult::LobbyNotExist;
            }
            client->send(resp);

            lobby->updateStatus();
        }
        case MsgType::LeaveLobby:
        {
            Lobby *lobby = client->lobby;
            if (client->lobby != nullptr) {
                client->lobby->removePlayer(client);

                LeaveLobbyResp resp;
                client->send(resp);
            }
            lobby->updateStatus();
        }
        case MsgType::DisbandLobby:
        {
            Lobby *lobby = client->lobby;
            if (client->lobby->getOwner() == client)
            {
                games->removeLobby(lobby->name);
            }
        }
        case MsgType::CloseLobbySlot:
        {
            Lobby *lobby = client->lobby;
            if (client->lobby->getOwner() == client)
            {
                CloseLobbySlot req{};
                packet >> req;
                client->lobby->closeSlot(req.slot);
            }
            lobby->updateStatus();
        }
        case MsgType::StartLobbyGame:
        {
            Lobby *lobby = client->lobby;
            if (client->lobby->getOwner() == client)
            {
                games->startGame(lobby);
            }
        }

        default:
        {
            break;
        }
    }
}
