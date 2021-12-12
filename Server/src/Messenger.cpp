#include "Messenger.hpp"

void Messenger::handleMessage(Server *server, std::shared_ptr<Client> &client, sf::Uint64 clientId, MessageId id, sf::Packet &packet)
{
    using namespace Msg;
    Games *games = &server->games;

    switch (id) {
        case MsgType::Logout:
        {
            SysLog::Print(SysLog::Severity::Info, "[%s] Logout",
                          client->username.c_str());
            server->timeoutList.push_back(clientId);
            break;
        }
        case MsgType::CreateLobby:
        {
            CreateLobby msg;
            packet >> msg;

            if (client->lobby) break;

            SysLog::Print(SysLog::Severity::Info, "[%s] CreateLobby - %s",
                          client->username.c_str(), msg.name.c_str());
            server->games.createLobby(client, msg.name, msg.mapFile, msg.mapName);
            client->status = ClientStatus::InLobby;
            break;
        }
        case MsgType::GetLobbyList:
        {
            GetLobbyListResp resp;
            resp.lobbies = games->getLobbyList();

            client->send(resp);
            break;
        }
        case MsgType::JoinLobby:
        {
            JoinLobby req;
            packet >> req;

            JoinLobbyResp resp{};
            Lobby * lobby = games->joinLobby(client, req.name);
            if (lobby) {
                resp.result = MessageResult::Ok;
                resp.mapFile = lobby->mapInfo.mapFile;
                resp.mapName = lobby->mapInfo.mapName;
            }
            else {
                resp.result = MessageResult::LobbyNotExist;
            }
            client->send(resp);
            break;
        }
        case MsgType::LeaveLobby:
        {
            Lobby *lobby = client->lobby;
            if (client->lobby != nullptr)
            {
                if (client->lobby->getOwner() == client)
                {
                    games->removeLobby(lobby->name);
                    break;
                }
                client->lobby->removePlayer(client);
            }

            LeaveLobbyResp resp;
            client->send(resp);
            break;
        }
        case MsgType::DisbandLobby: { break; } // included in leave lobby
        case MsgType::CloseLobbySlot:
        {
            Lobby *lobby = client->lobby;
            if (lobby != nullptr)
            {
                if (client->lobby->getOwner() == client) {
                    CloseLobbySlot req{};
                    packet >> req;
                    client->lobby->closeSlot(req.slot);
                }
                lobby->updateStatus();
            }
            break;
        }
        case MsgType::StartLobbyGame:
        {
            SysLog::Print(SysLog::Severity::Info, "Received StartLobbyGame");
            Lobby *lobby = client->lobby;
            if (lobby) {
                if (lobby->getOwner() == client) {
                    games->startGame(lobby);
                }
            }
            break;
        }

        default:
        {
            break;
        }
    }
}
