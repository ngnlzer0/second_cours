#include "Map.h"

Map::Map(int width, int height)
    : width(width), height(height), tiles(width* height, -1) {
}

void Map::setTile(int x, int y, int tileIndex) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[y * width + x] = tileIndex;
    }
}

int Map::getTile(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[y * width + x];
    }
    return -1; // Повертає -1, якщо координати виходять за межі карти
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}
