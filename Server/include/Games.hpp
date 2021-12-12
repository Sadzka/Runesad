#ifndef RUNESAD_GAMES_HPP
#define RUNESAD_GAMES_HPP
#include <memory>
#include <vector>
#include "Client.hpp"

#define MAX_PLAYERS 8

struct Slot
{
    sf::Uint8 closed = false;
    std::shared_ptr <Client> player;
};

struct Lobby
{
    std::string name;
    Slot slots[8];

    Lobby(const std::shared_ptr<Client>& client, std::string &game_name);

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
    void createLobby(const std::shared_ptr<Client>& client, std::string &name);
    void removeLobby(std::string &name);

    void startGame(Lobby * lobby);
};


#endif //RUNESAD_GAMES_HPP
