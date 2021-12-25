#ifndef RUNESAD_MAPINFO_HPP
#define RUNESAD_MAPINFO_HPP
#include <string>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <unordered_map>
#include <SFML/Config.hpp>

enum class TileType
{
    None = 0,
    Destroyable = 1,
    Collision = 2,
    DestroyingMissle = 4
};

struct MapInfo
{
    std::string mapFile;

    std::string mapName;
    sf::Vector2u size;
    std::vector<std::vector<std::vector<sf::Uint16>>> map;
    std::unordered_map <sf::Uint16, TileType> tilesType;
    sf::Vector2u flagPosition[2];
    sf::Vector2u startPosition[8];

    MapInfo(std::string &mapFile, std::string &mapName);
};


#endif //RUNESAD_MAPINFO_HPP
