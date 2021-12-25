#include "MapInfo.hpp"
#include <sstream>

MapInfo::MapInfo(std::string &mapFile, std::string &mapName) : mapFile(mapFile), mapName(mapName) {
    std::stringstream ss;
    printf("mapFile: %s \n\n", mapFile.c_str());
    ss << this->mapFile;

    // Ignored by server
    sf::Uint16 tilesNumber;
    std::string tilesName;

    ss  >> size.x >> size.y >> tilesNumber;
    for (int i = 0; i < tilesNumber; ++i) {
        ss >> tilesName;
    }
    // Ignored by server - end

    ss >> flagPosition[0].x >> flagPosition[0].y >> flagPosition[1].x >> flagPosition[1].y;

    const int layers = 3; // Server ignore layer 1 and 3
    map.resize(layers);
    for (int layer = 0; layer < layers; ++layer) {
        map[layer].resize(size.x);
        for (int x = 0; x < size.x; ++x) {
            map[layer][x].resize(size.y);
            for (int y = 0; y < size.x; ++y) {
                ss >> map[layer][x][y];
            }
        }
    }

    for (int i = 0; i < 8; ++i) {
        int x, y;
        ss >> x >> y;
        startPosition[i].x = x;
        startPosition[i].y = y;
        printf("mapInfo.startPosition[%d].x mapInfo.startPosition[%d].x: (%u, %u) \n",
               i, i, startPosition[i].x, startPosition[i].y);
    }

    sf::Uint16 i = 1;
    sf::Uint16 x;
    while (ss >> x)
    {
        tilesType.insert(std::make_pair(i, TileType(x)));
    }
}
