#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"

class TileMap {
public:
    TileMap(int width, int height);

    void setTile(int x, int y, const Tile& tile);
    Tile* getTile(int x, int y);

    int getWidth() const;
    int getHeight() const;

    void draw(sf::RenderWindow& window);

private:
    std::vector<std::vector<Tile>> tiles;
    int width;
    int height;
};

#endif // TILEMAP_H
