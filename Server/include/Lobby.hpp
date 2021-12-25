#ifndef RUNESAD_LOBBY_HPP
#define RUNESAD_LOBBY_HPP

#include <memory>
#include <Client.hpp>
#include <SFML/Config.hpp>
#include "MapInfo.hpp"
#include "Entity/Entity.hpp"

#define MAX_PLAYERS 8

struct Slot
{
    sf::Uint8 closed = false;
    std::shared_ptr <Client> player;
};

struct Lobby
{
    MapInfo mapInfo;
    std::string name;
    Slot slots[8];

    Lobby(const std::shared_ptr<Client>& client, std::string &game_name, std::string &mapInfo, std::string &mapName);

    bool removePlayer(const std::shared_ptr<Client>&);
    std::shared_ptr <Client> getOwner() { return slots[0].player; }

    void closeSlot(sf::Uint8 slot);
    void disband();
    void updateStatus();
};


#endif //RUNESAD_LOBBY_HPP
