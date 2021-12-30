#ifndef RUNESAD_GAMES_HPP
#define RUNESAD_GAMES_HPP
#include <memory>
#include <vector>
#include <unordered_map>
#include "Client.hpp"
#include "Game.hpp"
#include "Lobby.hpp"

class Games {
public:
    std::vector<std::string> getLobbyList();
    Lobby *joinLobby(const std::shared_ptr<Client>& client, std::string &name);
    void createLobby(const std::shared_ptr<Client>& client, std::string &name, std::string &mapInfo, std::string &mapName);
    void removeLobby(std::string &name);

    void startGame(Lobby * lobby);
    std::vector <Game*> &getGames() { return games; }
private:
    std::vector <Lobby> lobbies;
    std::vector <Game*> games;
};


#endif //RUNESAD_GAMES_HPP
