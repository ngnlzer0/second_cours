#pragma once
#include <vector>

class Map {
public:
    Map(int width, int height);
    void setTile(int x, int y, int tileIndex);
    int getTile(int x, int y) const;
    int getWidth() const;
    int getHeight() const;

private:
    int width, height;
    std::vector<int> tiles; // Зберігає індекси тайлів для кожної комірки
};
