#ifndef WFC_MAP_GENERATOR_H
#define WFC_MAP_GENERATOR_H

#include <map>
#include <vector>
#include <string>
#include "TileMap.h"
#include "Tile.h"

class WFCMapGenerator {
public:
    void initializeEntropy();
    WFCMapGenerator(TileMap& tileMap);
    void generate();

    const std::string name_f_texture = "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/world/Dungeon tileset.png";
    sf::Texture texture;

private:
    void collapse(int x, int y);
    int calculateEntropy(int x, int y);
    int selectTileByEntropy(int x, int y);
    std::vector<int> getPossibleTiles(int x, int y);

    TileMap& tileMap;
    static std::map<int, std::string> tileMapping; // Оголошення статичної змінної
    std::map<int, std::vector<int>> compatibilityMap;
};

#endif // WFC_MAP_GENERATOR_H
