#pragma once

#ifndef SADZA_WORLD_HPP
#define SADZA_WORLD_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "World/Tile.hpp"
#include "Tileset.hpp"

#define BLUE_FLAG_INDEX 0
#define RED_FLAG_INDEX 1
#define MAX_PLAYERS 8

class World {
    friend class WorldEditor;

public:
    World();

    ~World();

    sf::Int16 getTile(const sf::Vector2i &pos, const int &layer) const;

    sf::Int16 getTile(const int &x, const int &y, const int &layer) const;

//    sf::Int16 getTileOnPos(const sf::Vector2i &pos) const;
//
//    sf::Int16 getTileOnPos(const int &x, const int &y) const;

    void draw();

    void lateDraw();

    void loadWorld(const std::string &worldname);

    void saveWorld(const std::string &path);

    void resize(const sf::Vector2i &newSize);

    const sf::Vector2i &getSize() const;

    std::vector<Tileset> getTilesets();

    void drawHighlightedLayer(const int &layerNumber);

    void addTileset(const std::string &tilesetName);

    void removeTileset(const std::string &tilesetName);

    void clearTilesets();

    void closeWorld();

    Tile *getTileFromPosition(const sf::Vector2f &position);

    bool isPossitionCollidable(const sf::Vector2f &position);

    bool isPossitionDestroyable(const sf::Vector2f &position);

    bool isPossitionDestroyingMissle(const sf::Vector2f &position);

    sf::Vector2f getBlueFlagPosition() { return sf::Vector2f(flagPosition[BLUE_FLAG_INDEX].x, flagPosition[BLUE_FLAG_INDEX].y); }
    sf::Vector2f getRedFlagPosition() { return sf::Vector2f(flagPosition[RED_FLAG_INDEX].x, flagPosition[RED_FLAG_INDEX].y); }

    void destroyTile(sf::Vector2f position);

private:
    void allocateMemory();

    sf::Vector2u flagPosition[2];
    sf::Vector2u tanksPosition[MAX_PLAYERS];

    std::vector<Tileset> tilesets;
    sf::Vector2i size;
    //sf::Uint16 ***world;
    std::vector<std::vector<std::vector<sf::Uint16>>> world;
    std::string name;
    int tilesize;
    const int layersNumber;
    int tilesetIndex;
};


#endif //SADZA_WORLD_HPP
