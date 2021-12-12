#ifndef RUNESAD_GAMES_HPP
#define RUNESAD_GAMES_HPP
#include <memory>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Client.hpp"

#define MAX_PLAYERS 8

struct MapInfo
{
    std::string mapFile;

    std::string mapName;
    sf::Vector2u size;
    std::vector<std::vector<std::vector<sf::Uint16>>> map;
    sf::Vector2u flagPosition[2];

    MapInfo(std::string &mapFile, std::string &mapName);
};

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

struct Game
{
    Slot slots[MAX_PLAYERS];

    explicit Game(Lobby *lobby);
};

class Games {
    std::vector <Lobby> lobbies;
    std::vector <Game> games;
public:
    std::vector<std::string> getLobbyList();
    Lobby *joinLobby(const std::shared_ptr<Client>& client, std::string &name);
    void createLobby(const std::shared_ptr<Client>& client, std::string &name, std::string &mapInfo, std::string &mapName);
    void removeLobby(std::string &name);

    void startGame(Lobby * lobby);
};


#endif //RUNESAD_GAMES_HPP
