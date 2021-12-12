#pragma once

#ifndef SADZA_TILESET_HPP
#define SADZA_TILESET_HPP

#include <vector>
#include "Tile.hpp"

class Tileset {

public:
    Tileset(const std::string &tilesetName, const int &index);

    ~Tileset();

    sf::Vector2i getSize() const;

    sf::Vector2i getRange() const;

    Tile *inRange(const int &tileid);

    Tile *getTile(const int &id);

    unsigned int getTilesNumber() const;

    const std::string getName() const;

    int getOffset()const;

private:
    int offset;
    int tilesNumber;
    std::vector<Tile> tiles;
    int tilesize;
    std::string name;
    sf::Vector2i size;
};


#endif //SADZA_TILESET_HPP
