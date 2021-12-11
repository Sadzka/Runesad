#include "Games.hpp"
#include "Network/Messages/LeaveLobby.hpp"
#include "Network/Messages/UpdateLobbyStatus.hpp"
#include "Network/Messages/StartLobbyGame.hpp"

Lobby::Lobby(std::shared_ptr<Client> client, std::string &game_name) {
    slots[0].player = std::move(client);
}

bool Lobby::addPlayer(const std::shared_ptr<Client>& client)
{
    for (auto &slot : slots) {
        if (slot.player == nullptr && !slot.closed)
        {
            slot.player = client;
            return true;
        }
    }
    return false;
}

bool Lobby::removePlayer(const std::shared_ptr<Client> &client) {
    for (auto &slot : slots) {
        if (slot.player == client)
        {
            slot.player = nullptr;
            return true;
        }
    }
    return false;
}

void Lobby::disband() {
    Msg::LeaveLobbyResp resp;
    for (auto slot: slots)
    {
        if (slot.player != nullptr) {
            slot.player->send(resp);
        }
    }
}

void Lobby::updateStatus()
{
    Msg::UpdateLobbyStatus resp;
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        resp.open[i] = !slots[i].closed;
        if (slots[i].player != nullptr) {
            resp.playerName[i] = slots[i].player->username;
        }
    }

    for (auto slot: slots)
    {
        if (slot.player != nullptr) {
            slot.player->status = ClientStatus::Idle;
            slot.player->lobby = nullptr;
            slot.player->send(resp);
        }
    }
}

void Lobby::closeSlot(sf::Uint8 slot) {
    Msg::LeaveLobbyResp resp;

    Slot s = slots[slot];
    s.closed = s.closed;
    if (s.player != nullptr) {
        s.player->send(resp);
    }
}

void Games::createLobby(const std::shared_ptr<Client>& client, std::string &name)
{
    lobbies.emplace_back(client, name);
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
    for (auto &lobby : lobbies) {
        if (lobby.name == name)
        {
            for (auto & slot : lobby.slots) {
                if (slot.player == nullptr && !slot.closed)
                {
                    slot.player = client;
                    client->status = ClientStatus::InLobby;
                    client->lobby = &lobby;
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
            games.emplace_back(lobby);
            lobbies.erase(lobbies.begin() + i);
            return;
        }
    }
}

Game::Game(Lobby *lobby) {

    Msg::StartLobbyGame req;
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        slots[i] = lobby->slots[i];
        slots[i].player->send(req);
        slots[i].player->status = ClientStatus::InGame;
    }
}
