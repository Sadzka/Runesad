#include "World/Tile.hpp"
#include "Base/SharedContext.hpp"

Tile::Tile() {

};

void Tile::setTexture(const sf::Texture & texture, const sf::IntRect & rect) {
    this->sprite.setTexture(texture);
    this->sprite.setTextureRect(rect);
}

void Tile::draw(const int & x, const int & y) {
    this->sprite.setPosition(x * Tile::tilesize, y * Tile::tilesize);
    SharedContext::getWindow()->draw(sprite);
}

const sf::Texture *Tile::getTexture() {
    return sprite.getTexture();
}

sf::IntRect Tile::getTextureRect()const {
    return sprite.getTextureRect();
}

const int Tile::tilesize = 32;

void Tile::setId(const int &id) {
    this->id = id;
}

int Tile::getId() const {
    return id;
}

void Tile::setTransparent(const bool & transparent) {
    this->sprite.setColor(sf::Color(255, 255, 255, transparent ? 255 : 127));
}
