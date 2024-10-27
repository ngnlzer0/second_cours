#include "Tile.h"
Tile::Tile()
    : id(-1), sprite() {
    // Ініціалізація sprite або інших параметрів за замовчуванням, якщо потрібно
}

Tile::Tile(int id, sf::Texture* texture, const sf::IntRect& rect)
 {
    this->id = id;
    sprite.setTexture(*texture);
    sprite.setTextureRect(rect);
}

sf::Sprite Tile::getSprite() const {
    return sprite;
}

int Tile::getId() const {
    return id;
}

bool Tile::isEmpty() const {
    return id == -1; // Вважаємо, що тайл з id -1 є порожнім
}