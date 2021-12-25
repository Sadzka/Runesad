#include "Games.hpp"
#include "Network/Messages/UpdateLobbyStatus.hpp"

void Games::createLobby(const std::shared_ptr<Client>& client, std::string &name, std::string &mapInfo, std::string &mapName)
{
    lobbies.emplace_back(Lobby(client, name, mapInfo, mapName));
    lobbies.back().updateStatus();
    client->lobby = &lobbies.back();
}

std::vector<std::string> Games::getLobbyList() {
    std::vector<std::string> ret;
    for (auto &lobby: lobbies) {
        ret.push_back(lobby.name);
    }
    return ret;
}

void Games::removeLobby(std::string &name) {
    for (int i = 0; i < lobbies.size(); i++)
    {
        if (lobbies[i].name == name)
        {
            lobbies[i].disband();
            lobbies.erase(lobbies.begin()+i);
            return;
        }
    }
}

Lobby *Games::joinLobby(const std::shared_ptr<Client>& client, std::string &name) {
    for (auto &lobby : lobbies)
    {
        if (lobby.name == name)
        {
            for (auto &slot : lobby.slots)
            {
                if (slot.player == nullptr && !slot.closed)
                {
                    slot.player = client;
                    client->lobby = &lobby;
                    client->status = ClientStatus::InLobby;
                    lobby.updateStatus();
                    return &lobby;
                }
            }
            break;
        }
    }
    return nullptr;
}

void Games::startGame(Lobby *lobby) {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (lobbies[i].name == lobby->name) {
            Game game(lobby);
            games.emplace_back(game);
            lobbies.erase(lobbies.begin() + i);
            return;
        }
    }
}

