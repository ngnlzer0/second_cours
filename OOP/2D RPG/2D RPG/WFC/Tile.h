#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile {
public:
    Tile();
    Tile(int id, sf::Texture* texture, const sf::IntRect& rect);

    sf::Sprite getSprite() const;
    int getId() const;
    bool isEmpty() const; // Додаємо метод

private:
    int id;
    sf::Sprite sprite;
};

#endif // TILE_H
