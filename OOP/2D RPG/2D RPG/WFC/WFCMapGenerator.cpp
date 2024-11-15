#include "WFCMapGenerator.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>
/*
#pragma execution_character_set("utf-8")

// Ініціалізація статичної змінної tileMapping
std::map<int, std::string> WFCMapGenerator::tileMapping = {
    {0, "Лівий верхній край стіни"}, {1, "Середній верхній край стіни"}, {2, "Правий верхній край стіни"},
    {3, "Лівий середній край стіни"}, {4, "Середній стіни"}, {5, "Правий середній край стіни"},
    {6, "Лівий нижній край стіни"}, {7, "Середній нижній край стіни"}, {8, "Правий нижній край стіни"},
    {9, "Ліва банер"}, {10, "Права банер"}, {11, "Горизонтальна балка"},
    {12, "Вертикальна балка"}, {13, "Бочка"}, {14, "Факел"}, {15, "Розколота підлога"},
    {16, "Звичайна підлога"}, {17, "Відкриті двері зверху"}, {18, "Закриті двері"}, {19, "Ліва половина статуї"},
    {20, "Права половина статуї"}, {21, "Порожній ящик"}, {22, "Заповнений ящик"},
    {23, "Верхній край стовпа"}, {24, "Нижній край стовпа"}, {25, "Сходи"},
    {26, "Камінці"}, {27, "Зруйнована стіна"}, {28, "Зруйнована підлога"},
    {29, "Кам’яна підлога"}, {30, "Плитка підлоги"}
};

// Ініціалізація compatibilityMap
std::map<int, std::vector<int>> compatibilityMap = {
    {0, {1, 3, 4}}, {1, {0, 2, 4}}, {2, {1, 4, 5}}, {3, {0, 4, 6}},
    {4, {0, 1, 2, 3, 5, 6, 7, 8}}, {5, {2, 4, 8}}, {6, {3, 4, 7}},
    {7, {4, 6, 8}}, {8, {4, 5, 7}}, {9, {4, 10}}, {10, {4, 9}},
    {11, {4, 16}}, {12, {4, 16}}, {13, {16}}, {14, {4, 16}},
    {15, {16}}, {16, {11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 25, 26, 28, 29, 30}},
    {17, {16}}, {18, {4, 16}}, {19, {16, 20}}, {20, {16, 19}},
    {21, {16}}, {22, {16}}, {23, {4, 24}}, {24, {4, 23}},
    {25, {16}}, {26, {16}}, {27, {4, 16}}, {28, {16}}, {29, {16}}, {30, {16}}
};

// Конструктор
WFCMapGenerator::WFCMapGenerator(TileMap& tileMap)
    : tileMap(tileMap)
{
    texture.loadFromFile(name_f_texture);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    initializeAllPossibleTiles(); // Ініціалізація всіх можливих тайлів
}

// Ініціалізація всіх можливих тайлів
void WFCMapGenerator::initializeAllPossibleTiles() {
    int tileCount = tileMapping.size();
    for (int id = 0; id < tileCount; ++id) {
        Tile tile(id, &texture, sf::IntRect(
            (id % (texture.getSize().x / TILE_WIDTH)) * TILE_WIDTH,
            (id / (texture.getSize().x / TILE_WIDTH)) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT));
        allPossibleTiles.push_back(tile);
    }
}

// Ініціалізація ентропії
void WFCMapGenerator::initializeEntropy() {
    for (int y = 0; y < tileMap.getHeight(); ++y) {
        for (int x = 0; x < tileMap.getWidth(); ++x) {
            for (const Tile& tile : allPossibleTiles) {
                tileMap->getTile(x, y).addPossibleTile(tile);
            }
        }
    }
}

// Обчислення ентропії
int WFCMapGenerator::calculateEntropy(int x, int y) {
    return tileMap.getTile(x, y).getPossibleTiles().size();
}

// Колапс клітини
void WFCMapGenerator::collapse(int x, int y) {
    int selectedTileId = selectTileByEntropy(x, y);
    if (selectedTileId != -1) {
        Tile tile(selectedTileId, &texture, sf::IntRect(
            (selectedTileId % (texture.getSize().x / TILE_WIDTH)) * TILE_WIDTH,
            (selectedTileId / (texture.getSize().x / TILE_WIDTH)) * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT));
        tileMap.setTile(x, y, tile);
    }
}

// Вибір тайла за ентропією
int WFCMapGenerator::selectTileByEntropy(int x, int y) {
    const std::vector<int>& possibleTiles = getPossibleTiles(x, y);
    if (possibleTiles.empty()) return -1;
    return possibleTiles[std::rand() % possibleTiles.size()];
}

// Отримання можливих тайлів
std::vector<int> WFCMapGenerator::getPossibleTiles(int x, int y) {
    std::vector<int> possibleTiles;
    for (const auto& [tileId, compatibleTiles] : compatibilityMap) {
        bool isCompatible = true;

        // Перевірка сусідів
        if (x > 0 && tileMap.getTile(x - 1, y).isCollapsed()) {
            int leftTileId = tileMap.getTile(x - 1, y).getId();
            isCompatible &= (std::find(compatibleTiles.begin(), compatibleTiles.end(), leftTileId) != compatibleTiles.end());
        }
        if (y > 0 && tileMap.getTile(x, y - 1).isCollapsed()) {
            int topTileId = tileMap.getTile(x, y - 1).getId();
            isCompatible &= (std::find(compatibleTiles.begin(), compatibleTiles.end(), topTileId) != compatibleTiles.end());
        }

        if (isCompatible) {
            possibleTiles.push_back(tileId);
        }
    }
    return possibleTiles;
}

*/