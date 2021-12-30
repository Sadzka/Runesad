#include "World/Tileset.hpp"
#include "Base/SharedContext.hpp"

Tileset::Tileset(const std::string &tilesetName, const int &index) : offset(index), tilesNumber(0) {
    this->name = tilesetName;
    tilesize = static_cast<int>(SharedContext::getVariables()->getVariable("_tilesize"));
    const sf::Texture tileset = SharedContext::getTextureManager()->
            loadResource("data/img/tilesets/" + tilesetName + ".png");

    size.x = tileset.getSize().x / tilesize;
    size.y = tileset.getSize().y / tilesize;
    int no = offset;
    for (unsigned int i = 0; i < size.x; ++i) {
        for (unsigned int j = 0; j < size.y; ++j) {
            Tile tile;
            tile.setId(no++);
            tile.setTexture(
                    SharedContext::getTextureManager()->loadResource("data/img/tilesets/" + tilesetName + ".png"),
                    sf::IntRect(i * tilesize, j * tilesize, tilesize, tilesize));
            this->tiles.push_back(tile);
            this->tilesNumber++;
        }
    }
}

Tileset::~Tileset() {
    tiles.clear();
}

sf::Vector2i Tileset::getSize() const {
    return size;
}

sf::Vector2i Tileset::getRange() const {
    return sf::Vector2i(this->offset, this->offset + this->tilesNumber);
}

Tile *Tileset::getTile(const int &id) {
    return &this->tiles[id - offset];
}

unsigned int Tileset::getTilesNumber() const {
    return this->tilesNumber;
}

Tile *Tileset::inRange(const int &tileid) {
    if (tileid >= offset && tileid < offset + tilesNumber) {
        return &tiles[tileid - offset];
    }
    return nullptr;
}

const std::string Tileset::getName() const {
    return name;
}

int Tileset::getOffset() const {
    return offset;
}
