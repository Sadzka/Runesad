#pragma once

#ifndef SADZA_TILE_HPP
#define SADZA_TILE_HPP

#include <SFML/Graphics.hpp>
#include <TGUI/Texture.hpp>

enum class TileType
{
    None = 0,
    Destroyable = 1,
    Collision = 2,
    DestroyingMissle = 4
};

class Tile {
public:
    Tile();

    void setTexture(const sf::Texture &texture, const sf::IntRect &rect);

    void draw(const int &x, const int &y);

    const sf::Texture *getTexture();

    sf::IntRect getTextureRect()const;

    int getId() const;

    void setId(const int &id);

    void setTransparent(const bool & transparent);

    void setType(int type);

    [[nodiscard]] int getType() const { return tileType; }

    [[nodiscard]] bool isCollidable() const { return tileType & int(TileType::Collision); }
    [[nodiscard]] bool isDestroyable() const { return tileType & int(TileType::Destroyable); }
    [[nodiscard]] bool isDestroyingMissle() const { return tileType & int(TileType::DestroyingMissle); }
private:

    static const int tilesize;
    int id;
    sf::Sprite sprite;
    int tileType;
};


#endif //SADZA_TILE_HPP
