#ifndef RUNESAD_GAME_HPP
#define RUNESAD_GAME_HPP

#include "MapInfo.hpp"
#include "Lobby.hpp"
#include "Entity/Entity.hpp"

struct Game
{
    MapInfo mapInfo;
    Slot slots[MAX_PLAYERS];
    Entity entity[MAX_PLAYERS];
    std::vector < Entity > missles;

    sf::Uint32 nextUnitId = MAX_PLAYERS;
    explicit Game(Lobby *lobby);

    template < class T >
    void sendToAll(const T &t) {
        for (auto &slot : slots) {
            if (slot.player != nullptr) {
                slot.player->send(t);
            }
        }
    }
};


#endif //RUNESAD_GAME_HPP
