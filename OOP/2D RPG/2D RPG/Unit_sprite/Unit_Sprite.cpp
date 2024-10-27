#include "Unit_Sprite.h"

// Реалізація конструктора
Unit_Sprite::Unit_Sprite(const std::string& texture_file, sf::Vector2f position, sf::Vector2f scale)
    : animation(0.1f) { // Наприклад, 0.1 секунда між кадрами
    if (!texture.loadFromFile(texture_file)) {
        throw std::runtime_error("Unable to load texture from file: " + texture_file);
    }

    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(scale);
}

void Unit_Sprite::update(float deltaTime) {
    animation.update(deltaTime);
    sprite.setTextureRect(animation.getCurrentFrame());
}

void Unit_Sprite::render(sf::RenderTarget& target) {
    target.draw(sprite);
}

void Unit_Sprite::addAnimationFrame(const sf::IntRect& frame) {
    animation.addFrame(frame);
}

void Unit_Sprite::setPosition(sf::Vector2f position) {
    sprite.setPosition(position);
}

void Unit_Sprite::setScale(sf::Vector2f scale) {
    sprite.setScale(scale);
}

