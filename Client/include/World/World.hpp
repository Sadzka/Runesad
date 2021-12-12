#pragma once

#ifndef SADZA_WORLD_HPP
#define SADZA_WORLD_HPP


#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "World/Tile.hpp"
#include "Tileset.hpp"

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

private:
    void allocateMemory();


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
