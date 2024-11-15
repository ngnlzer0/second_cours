#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <map>

const int TILE_WIDTH = 16;
const int TILE_HEIGHT = 16;

class Tile {
public:
    Tile();  // За замовчуванням
    Tile(int id, sf::Texture* texture);  // Конструктор з ID та текстурою
    Tile(int id, sf::Texture* texture, sf::IntRect textureRect)
        : id(id), texture(texture), rect(textureRect) {
        sprite.setTexture(*texture);
        sprite.setTextureRect(rect);
    }

    sf::Sprite getSprite() const;
    int getId() const;
    bool isEmpty() const;  // Перевірка на порожність
    sf::Texture* getTexture() {
        return texture;
    }

    void addPossibleTile(const Tile& tile) {
        possibleTiles.push_back(tile);
    }

    // Отримати кількість можливих тайлів
    int getEntropy() const {
        return possibleTiles.size();
    }

    // Очистити список можливих тайлів і залишити лише один
    void collapseToTile(const Tile& tile) {
        possibleTiles.clear();
        possibleTiles.push_back(tile);
    }

private:
    int id;                  // ID тайла
    sf::Sprite sprite;       // Спрайт тайла
    sf::IntRect rect;        // Прямокутник для текстури
    sf::Texture* texture;    // Текстура для тайла

    std::vector<Tile> possibleTiles;
    static std::map<int, sf::IntRect> tileMapping; // Мапа ID -> частини текстури
};

#endif // TILE_H

