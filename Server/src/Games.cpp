#include "Games.hpp"

#include <sstream>
#include <utility>
#include "Network/Messages/LeaveLobby.hpp"
#include "Network/Messages/UpdateLobbyStatus.hpp"
#include "Network/Messages/StartLobbyGame.hpp"

Lobby::Lobby(const std::shared_ptr<Client>& client, std::string &game_name, std::string &mapInfoStr, std::string &mapName)
        : mapInfo(mapInfoStr, mapName) {
    printf("owner: %p \n", &(*client));
    slots[0].player = client;
    printf("owner: %p \n", &(*slots[0].player));
    name = game_name;
}

bool Lobby::removePlayer(const std::shared_ptr<Client> &client) {
    Msg::LeaveLobbyResp resp;
    for (auto &slot : slots) {
        if (slot.player == client)
        {
            slot.player->send(resp);
            slot.player = nullptr;
            updateStatus();
            return true;
        }
    }
    return false;
}

void Lobby::disband() {
    Msg::LeaveLobbyResp resp;
    for (const auto& slot: slots)
    {
        if (slot.player != nullptr) {
            slot.player->send(resp);
        }
    }
}

void Lobby::updateStatus()
{
    Msg::UpdateLobbyStatus resp{};
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        resp.open[i] = !slots[i].closed;
        resp.playerName[i] = "";
        if (slots[i].player != nullptr) {
            resp.open[i] = false;
            resp.playerName[i] = slots[i].player->username;
        }
    }

    for (auto &slot: slots)
    {
        if (slot.player != nullptr) {
            slot.player->send(resp);
        }
    }
}

void Lobby::closeSlot(sf::Uint8 slot) {
    Msg::LeaveLobbyResp resp;

    Slot &s = slots[slot];
    s.closed = !s.closed;
    if (s.player != nullptr) {
        s.player->send(resp);
    }
    updateStatus();
}

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

Game::Game(Lobby *lobby) {

    Msg::StartLobbyGame req;
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        slots[i].player = lobby->slots[i].player;
        slots[i].closed = lobby->slots[i].closed;
        if (slots[i].player != nullptr)
        {
            slots[i].player->send(req);
            slots[i].player->status = ClientStatus::InGame;
            slots[i].player->lobby = nullptr;
            slots[i].player->game = this;
        }
    }
}

MapInfo::MapInfo(std::string &mapFile, std::string &mapName) : mapFile(mapFile), mapName(mapName) {
    std::stringstream ss;
    ss << this->mapFile;

    // Ignored by server
    sf::Uint16 tilesNumber;
    std::string tilesName;

    ss  >> size.x >> size.y >> tilesNumber;
    for (int i = 0; i < tilesNumber; ++i) {
        ss >> tilesName;
    }
    // Ignored by server - end

    ss >> flagPosition[0].x >> flagPosition[0].y >> flagPosition[1].x >> flagPosition[1].y;

    const int layers = 2; // Server ignore layer 3
    map.resize(layers);
    for (int layer = 0; layer < layers; ++layer) {
        map[layer].resize(size.x);
        for (int x = 0; x < size.x; ++x) {
            map[layer].resize(size.y);
            for (int y = 0; y < size.x; ++y) {
                ss >> map[layer][x][y];
            }
        }
    }
}
