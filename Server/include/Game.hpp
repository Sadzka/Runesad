#ifndef RUNESAD_GAME_HPP
#define RUNESAD_GAME_HPP

#include "MapInfo.hpp"
#include "Lobby.hpp"
#include "Entity/Entity.hpp"
#include "Network/Messages/Base/AllMessages.hpp"

struct Game
{
    MapInfo mapInfo;
    Slot slots[MAX_PLAYERS];
    Entity entity[MAX_PLAYERS];
    std::vector < Entity > missiles;

    explicit Game(Lobby *lobby);

    template < class T >
    void sendToAll(const T &t) {
        static int i = 0;
        for (auto &slot : slots) {
            if (slot.player != nullptr) {
                slot.player->send(t);
            }
        }
    }

    void createShot(std::shared_ptr<Client>& client, sf::Vector2f &position, sf::Uint8 dir);
    sf::Uint32 getNextUnitId() { return nextUnitId++; }

    void handleMoveInd(const Msg::MoveInd &ind);

    void handleDestroyInd(Msg::DestroyInd ind);

    void handleDestroyTileInd(Msg::DestroyTileInd ind);

private:
    const sf::Uint32 blueFlagId     = MAX_PLAYERS;
    const sf::Uint32 redFlagId      = MAX_PLAYERS + 1;
    sf::Uint32 nextUnitId           = MAX_PLAYERS + 2;
};


#endif //RUNESAD_GAME_HPP
