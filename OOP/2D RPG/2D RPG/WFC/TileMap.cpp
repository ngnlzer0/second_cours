#include "TileMap.h"

TileMap::TileMap(int width, int height)
    : width(width), height(height) {
    tiles.resize(height, std::vector<Tile>(width)); // Ініціалізація двовимірного вектора тайлів
}

void TileMap::setTile(int x, int y, const Tile& tile) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[y][x] = tile; // Встановлюємо тайл у мапу
    }
}

Tile* TileMap::getTile(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return &tiles[y][x]; // Повертаємо вказівник на тайл
    }
    return nullptr; // Якщо виходимо за межі
}

int TileMap::getWidth() const {
    return width; // Повертаємо ширину мапи
}

int TileMap::getHeight() const {
    return height; // Повертаємо висоту мапи
}

void TileMap::draw(sf::RenderWindow& window) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Tile& tile = tiles[y][x];
            if (!tile.isEmpty()) { // Перевірка на порожній тайл
                window.draw(tile.getSprite()); // Малюємо спрайт тайла
            }
        }
    }
}

