#include <Network/Messages/Base/AllMessages.hpp>
#include "Lobby.hpp"

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