#include "WFCMapGenerator.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>

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

WFCMapGenerator::WFCMapGenerator(TileMap& tileMap)
    : tileMap(tileMap)
{
    texture.loadFromFile(name_f_texture);
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void WFCMapGenerator::generate() {
    while (true) {
        // Знайти клітину з найменшою ентропією
        int minEntropy = INT_MAX;
        std::pair<int, int> minCoords(-1, -1);

        for (int y = 0; y < tileMap.getHeight(); ++y) {
            for (int x = 0; x < tileMap.getWidth(); ++x) {
                int entropy = calculateEntropy(x, y);
                if (entropy > 1 && entropy < minEntropy) {
                    minEntropy = entropy;
                    minCoords = { x, y };
                }
            }
        }

        // Якщо не знайдено більше клітин для колапсу, вийти
        if (minCoords.first == -1) break;

        // Виконати колапс для клітини з найменшою ентропією
        collapse(minCoords.first, minCoords.second);
    }
}

int WFCMapGenerator::calculateEntropy(int x, int y) {
    std::vector<int> possibleTiles = getPossibleTiles(x, y);
    return static_cast<int>(possibleTiles.size());
}

int WFCMapGenerator::selectTileByEntropy(int x, int y) {
    std::vector<int> possibleTiles = getPossibleTiles(x, y);
    if (possibleTiles.empty()) return -1; // Якщо немає можливих тайлів

    // Вибираємо випадковий тайл з можливих
    int randomIndex = std::rand() % possibleTiles.size();
    return possibleTiles[randomIndex];
}

void WFCMapGenerator::collapse(int x, int y) {
    int selectedTileId = selectTileByEntropy(x, y);
    if (selectedTileId != -1) {
        int tileWidth = 32;  // ширина тайла, змініть на фактичну
        int tileHeight = 32; // висота тайла, змініть на фактичну
        Tile tile(selectedTileId, &texture, sf::IntRect(
            (selectedTileId % (texture.getSize().x / tileWidth)) * tileWidth,
            (selectedTileId / (texture.getSize().x / tileWidth)) * tileHeight,
            tileWidth, tileHeight
        ));
        tileMap.setTile(x, y, tile); // Установка тайла в мапу
    }
}

std::vector<int> WFCMapGenerator::getPossibleTiles(int x, int y) {
    std::vector<int> possibleTiles;

    // Перебираємо всі тайли у compatibilityMap
    for (const auto& entry : compatibilityMap) {
        int tileId = entry.first; // Отримуємо ID тайла
        const std::vector<int>& compatibleTiles = entry.second; // Отримуємо вектор сумісних тайлів

        bool isCompatible = true;

        // Перевірка лівого тайла
        if (x > 0 && tileMap.getTile(x - 1, y)) {
            int leftTileId = tileMap.getTile(x - 1, y)->getId();
            isCompatible &= (std::find(compatibleTiles.begin(), compatibleTiles.end(), leftTileId) != compatibleTiles.end());
        }

        // Перевірка верхнього тайла
        if (y > 0 && tileMap.getTile(x, y - 1)) {
            int topTileId = tileMap.getTile(x, y - 1)->getId();
            isCompatible &= (std::find(compatibleTiles.begin(), compatibleTiles.end(), topTileId) != compatibleTiles.end());
        }

        // Якщо тайл сумісний, додаємо його до списку можливих тайлів
        if (isCompatible) {
            possibleTiles.push_back(tileId);
        }
    }

    return possibleTiles;
}



