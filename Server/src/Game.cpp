#include <Network/Messages/Base/AllMessages.hpp>
#include <Client.hpp>
#include "Game.hpp"

Game::Game(Lobby *lobby) : mapInfo(lobby->mapInfo) {

    Msg::StartLobbyGame req{};
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
            req.playerId = i;
            //
            slot->player->send(req);
            slot->player->status = ClientStatus::InGame;
            slot->player->lobby = nullptr;
            slot->player->game = this;
        }
        else {
            slots[i].player = nullptr;
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

    Msg::UpdateUnitInd blueFlag;
    blueFlag.destroy = false;
    blueFlag.direction = Direction::Up;
    blueFlag.unitId = blueFlagId;
    blueFlag.position = sf::Vector2f(mapInfo.flagPosition[0].x*32 + 16, mapInfo.flagPosition[0].y*32 + 16);
    blueFlag.type = static_cast<unsigned char>(EntityType::FlagBlue);

    Msg::UpdateUnitInd redFlag;
    redFlag.destroy = false;
    redFlag.direction = Direction::Up;
    redFlag.unitId = redFlagId;
    redFlag.position = sf::Vector2f(mapInfo.flagPosition[1].x*32 + 16, mapInfo.flagPosition[1].y*32 + 16);
    redFlag.type = static_cast<unsigned char>(EntityType::FlagRed);

    sendToAll(blueFlag);
    sendToAll(redFlag);
}

void Game::createShot(std::shared_ptr<Client> &client, sf::Vector2f &position, sf::Uint8 dir) {

    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (slots[i].player == client) {
            Entity &clientEntity = client->game->entity[i];

            Entity missile;
            missile.id = getNextUnitId();
            missiles.push_back(missile);

            Msg::UpdateUnitInd ind;
            ind.unitId = missile.id;
            ind.type = static_cast<sf::Uint8>(EntityType::Missile);
            ind.direction = static_cast<Direction>(dir);
            ind.position = position;
            ind.destroy = false;

            static const float missileOffset = 48.0f;
            switch (Direction(dir))
            {
                case Direction::Up:
                    ind.position.y -= missileOffset;
                    break;
                case Direction::Right:
                    ind.position.x += missileOffset;
                    break;
                case Direction::Down:
                    ind.position.y += missileOffset;
                    break;
                case Direction::Left:
                    ind.position.x -= missileOffset;
                    break;
            }

            sendToAll(ind);

            Msg::MoveInd moveInd{};
            moveInd.direction = dir;
            moveInd.start = true;
            moveInd.unitId = missile.id;

            sendToAll(moveInd);

            return;
        }
    }
}

void Game::handleMoveInd(const Msg::MoveInd &ind) {
    sendToAll(ind);
}

void Game::handleDestroyTileInd(Msg::DestroyTileInd ind) {
    sendToAll(ind);
}

void Game::handleDestroyInd(Msg::DestroyInd ind) {
    sendToAll(ind);

    Msg::EndGameInd victoryInd{};
    victoryInd.victory = true;
    Msg::EndGameInd defeatInd{};
    victoryInd.victory = true;

    if (ind.entityId == redFlagId) {
        for (int i = 0; i < 4; ++i) {
            if (slots[i].player != nullptr) slots[i].player->send(victoryInd);
        }
        for (int i = 4; i < MAX_PLAYERS; ++i) {
            if (slots[i].player != nullptr) slots[i].player->send(defeatInd);
        }
    }
    else if  (ind.entityId == blueFlagId) {
        for (int i = 0; i < 4; ++i) {
            if (slots[i].player != nullptr) slots[i].player->send(defeatInd);
        }
        for (int i = 4; i < MAX_PLAYERS; ++i) {
            if (slots[i].player != nullptr) slots[i].player->send(victoryInd);
        }
    }
}
