#include <Network/Messages/Base/AllMessages.hpp>
#include <Client.hpp>
#include "Game.hpp"

Game::Game(Lobby *lobby) : mapInfo(lobby->mapInfo) {

    Msg::StartLobbyGame req;
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        Slot *slot = &slots[i];
        slots[i].player = lobby->slots[i].player;
        slots[i].closed = lobby->slots[i].closed;
        if (slot->player != nullptr)
        {
            // Create Entities
            entity[i].id = i;
            entity[i].type = ( i < 4 ? EntityType::BlueTank : EntityType::RedTank);
            entity[i].direction = (i < 4 ? Direction::Up : Direction::Down);
            entity[i].position = sf::Vector2f(mapInfo.startPosition[i].x * 32 + 16, mapInfo.startPosition[i].y * 32 + 16);
            //
            slot->player->send(req);
            slot->player->status = ClientStatus::InGame;
            slot->player->lobby = nullptr;
            slot->player->game = this;
        }
    }

    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (slots[i].player != nullptr) {
            Msg::UpdateUnitInd ind;
            ind.unitId      = entity[i].id;
            ind.type        = sf::Uint8 (entity[i].type);
            ind.direction   = entity[i].direction;
            ind.position    = entity[i].position;
            ind.destroy     = false;
            sendToAll(ind);
        }
    }
}