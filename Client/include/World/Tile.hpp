#pragma once

#ifndef SADZA_TILE_HPP
#define SADZA_TILE_HPP

#include <SFML/Graphics.hpp>
#include <TGUI/Texture.hpp>

class Tile {
    sf::Sprite sprite;
public:
    int getId() const;

private:
    int id;
public:
    Tile();

    void setTexture(const sf::Texture &texture, const sf::IntRect &rect);

    void draw(const int &x, const int &y);

    const sf::Texture *getTexture();

    sf::IntRect getTextureRect()const;

    void setId(const int &id);

    void setTransparent(const bool & transparent);
private:
    static const int tilesize;
};


#endif //SADZA_TILE_HPP
