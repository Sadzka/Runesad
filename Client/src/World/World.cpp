//
// Created  on 13.06.2021.
//

#include "World/World.hpp"
#include "Base/SharedContext.hpp"


World::World() : layersNumber(3) {
    //world = nullptr;
    name = "Unknown";
    tilesize = SharedContext::getVariables()->getVariable("_tilesize");
}

World::~World() {
    closeWorld();
}

sf::Int16 World::getTile(const sf::Vector2i &pos, const int &layer) const { return world[layer][pos.x][pos.y]; }

sf::Int16 World::getTile(const int &x, const int &y, const int &layer) const { return world[layer][x][y]; }

const sf::Vector2i &World::getSize() const {
    return size;
}

void World::loadWorld(const std::string &worldname) {

    closeWorld();
    std::string filename = worldname.find(".map") == std::string::npos
            ? worldname
            : worldname.substr(0, worldname.length()-4);

    std::ifstream file("data/maps/" + filename + ".map");
    if (!file.is_open()) {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        throw std::runtime_error("Could not open map file " + worldname + "\n");
    }

    name = worldname;

    file >> size.x >> size.y;
    allocateMemory();

    int tilesetsNumber;
    file >> tilesetsNumber;

    for (int i = 0; i < tilesetsNumber; i++) {
        std::string tilesetName;
        file >> tilesetName;
        addTileset(tilesetName);
    }

    file >> flagPosition[BLUE_FLAG_INDEX].x >> flagPosition[BLUE_FLAG_INDEX].y;
    file >> flagPosition[RED_FLAG_INDEX].x  >> flagPosition[RED_FLAG_INDEX].y;

    for (unsigned int layer = 0; layer < layersNumber; layer++) {
        for (unsigned int i = 0; i < size.y; i++) {
            for (unsigned int j = 0; j < size.x; j++) {
                file >> world[layer][j][i];
            }
        }
    }

    for (auto & i : tanksPosition) {
        file >> i.x >> i.y;
    }

    for (auto &tileset : tilesets) {
        for (auto &tile : tileset.getTiles()) {
            int tileType;
            file >> tileType;
            tile.setType(tileType);
        }
    }

    file.close();
}

void World::saveWorld(const std::string &path) {
    std::cout << "path " << path << std::endl;

    std::fstream file;
    file.open("data/maps/" + (path == "" ? name : path) + ".map", std::ios::out);
    std::cout << "out " << "data/maps/" + (path == "" ? name : path) << std::endl;


    if (!file.is_open()) {
        std::cerr << "Error: " << strerror(errno) << std::endl;
        throw std::runtime_error("Could not save file" + path + "\n");
    }
    file << size.x << " "
         << size.y << "\n"
         << tilesets.size() << " ";
    for (auto tileset : tilesets) {
        file << tileset.getName() << " ";
    }
    file << "\n";

    file << flagPosition[BLUE_FLAG_INDEX].x << ' ' << flagPosition[BLUE_FLAG_INDEX].y << '\n';
    file << flagPosition[RED_FLAG_INDEX].x  << ' ' << flagPosition[RED_FLAG_INDEX].y << '\n';

    for (unsigned int layer = 0; layer < layersNumber; layer++) {
        for (unsigned int i = 0; i < size.y; i++) {
            for (unsigned int j = 0; j < size.x; j++) {
                file << world[layer][j][i] << " ";
            }
            file << "\n";
        }
        file << "\n";
    }

    for (auto & i : tanksPosition) {
        file << i.x << ' ' << i.y << '\n';
    }

    for (auto &tileset : tilesets) {
        for (const auto& tile : tileset.getTiles()) {
            int tileType = tile.getType();
            file << tileType << " ";
        }
    }

    file.close();
}

void World::draw() {

    sf::View view = SharedContext::getWindow()->getRenderWindow()->getView();
    sf::FloatRect vp = sf::FloatRect(
            view.getCenter().x - view.getSize().x / 2,
            view.getCenter().y - view.getSize().y / 2,
            view.getSize().x,
            view.getSize().y
    );

    sf::RectangleShape rect(sf::Vector2f(32, 32));
    rect.setFillColor(sf::Color::White);

    for (int layer = 0; layer < layersNumber; ++layer) {
        for (int i = vp.left / tilesize; i < (vp.left + vp.width) / tilesize && i < size.x; i++) {
            for (int j = vp.top / tilesize; j < (vp.top + vp.height) / tilesize && j < size.y; j++) {

                if (i < 0 || j < 0) { continue; }

                if (world[layer][i][j] == 0 && layer == 0) {
                    rect.setPosition(i * 32, j * 32);
                    SharedContext::getWindow()->draw(rect);
                    continue;
                }

                for (Tileset &tileset : tilesets) {
                    Tile *tile = tileset.inRange(world[layer][i][j]);
                    if (tile) {
                        tile->draw(i, j);
                        continue;
                    }
                }
            }
        }
    }
}

void World::lateDraw() {

    sf::View view = SharedContext::getWindow()->getRenderWindow()->getView();
    sf::FloatRect vp = sf::FloatRect(
            view.getCenter().x - view.getSize().x / 2,
            view.getCenter().y - view.getSize().y / 2,
            view.getSize().x,
            view.getSize().y
    );

    sf::RectangleShape rect(sf::Vector2f(32, 32));
    rect.setFillColor(sf::Color::White);
    int layer = 2;
    for (int i = vp.left / tilesize; i < (vp.left + vp.width) / tilesize && i < size.x; i++) {
        for (int j = vp.top / tilesize; j < (vp.top + vp.height) / tilesize && j < size.y; j++) {

            if (i < 0 || j < 0) { continue; }

            if (world[layer][i][j] == 0 && layer == 0) {
                rect.setPosition(i * 32, j * 32);
                SharedContext::getWindow()->draw(rect);
                continue;
            }

            for (Tileset &tileset : tilesets) {
                Tile *tile = tileset.inRange(world[layer][i][j]);
                if (tile) {
                    tile->draw(i, j);
                    continue;
                }
            }
        }
    }
}

void World::drawHighlightedLayer(const int &layerNumber) {

    sf::View view = SharedContext::getWindow()->getRenderWindow()->getView();
    sf::FloatRect vp = sf::FloatRect(
            view.getCenter().x - view.getSize().x / 2,
            view.getCenter().y - view.getSize().y / 2,
            view.getSize().x,
            view.getSize().y
    );

    sf::RectangleShape rect(sf::Vector2f(32, 32));
    rect.setFillColor(sf::Color::White);

    for (int layer = 0; layer < layersNumber; ++layer) {
        for (int i = vp.left / tilesize; i < (vp.left + vp.width) / tilesize && i < size.x; i++) {
            for (int j = vp.top / tilesize; j < (vp.top + vp.height) / tilesize && j < size.y; j++) {

                if (i < 0 || j < 0) { continue; }

                if (world[layer][i][j] == 0 && layer == 0) {
                    rect.setPosition(i * 32, j * 32);
                    SharedContext::getWindow()->draw(rect);
                    continue;
                }

                for (Tileset &tileset : tilesets) {
                    Tile *tile = tileset.inRange(world[layer][i][j]);
                    if (tile) {
                        tile->setTransparent(layer == layerNumber);
                        tile->draw(i, j);
                        continue;
                    }
                }
            }
        }
    }
}

void World::allocateMemory() {
    world.resize(layersNumber);
    for (int i = 0; i < layersNumber; ++i) {
        world[i].resize(size.x);
        for (int j = 0; j < size.x; ++j) {
            world[i][j].resize(size.y);
        }
    }
}

void World::closeWorld() {
    world.resize(layersNumber);
    for (int i = 0; i < layersNumber; ++i) {
        for (int j = 0; j < size.y; ++j) {
            world[i][j].clear();
        }
        world[i].clear();
    }
    world.clear();

    size = sf::Vector2i(0, 0);
    name = "Unknown";
    clearTilesets();
}

void World::resize(const sf::Vector2i &newSize) {
    size = newSize;
    world.resize(layersNumber);
    for (int i = 0; i < layersNumber; ++i) {
        world[i].resize(size.x);
        for (int j = 0; j < size.x; ++j) {
            world[i][j].resize(size.y);
        }
    }
}

std::vector<Tileset> World::getTilesets() {
    return this->tilesets;
}

void World::addTileset(const std::string &tilesetName) {
    Tileset tileset(tilesetName, tilesetIndex);
    tilesetIndex += tileset.getTilesNumber();
    tilesets.push_back(tileset);
}

void World::removeTileset(const std::string &tilesetName) {
    std::vector < std::string > tilesetNames;
    sf::Vector2i range;
    sf::Uint32 tileOffset;
    for (const Tileset & tileset : tilesets) {
        if (tileset.getName() != tilesetName) {
            tilesetNames.push_back(tileset.getName());
        }
        else {
            range = tileset.getRange();
            tileOffset = tileset.getTilesNumber();
        }
    }

    if (tilesets.size() == tilesetNames.size()) { // no tileset removed
        return;
    }

    for (int layer = 0; layer < layersNumber; ++layer) {
        for (int i = 0; i < size.x; i++) {
            for (int j = 0; j < size.y; j++) {

                if (world[layer][i][j] < range.x) { continue; }
                else if (world[layer][i][j] >= range.x && world[layer][i][j] < range.y) {
                    world[layer][i][j] = 0;
                }
                else {
                    world[layer][i][j] -= tileOffset;
                }
            }
        }
    }

    clearTilesets();
    for (const std::string & str : tilesetNames) {
        addTileset(str);
    }
}

void World::clearTilesets() {
    tilesets.clear();
    tilesetIndex = 1;
}

