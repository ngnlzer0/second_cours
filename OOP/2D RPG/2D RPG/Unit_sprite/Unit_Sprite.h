#pragma once
#include "Animation/Animation.h" // Необхідно для використання класу Animation

class Unit_Sprite {
private:
    sf::Sprite sprite;              // Спрайт для відображення
    sf::Texture texture;            // Текстура
    Animation animation;            // Анімація

public:
    Unit_Sprite(const std::string& texture_file = "", sf::Vector2f position = {}, sf::Vector2f scale = { 1.f, 1.f });

    void update(float deltaTime);             // Оновлює анімацію
    void render(sf::RenderTarget& target);   // Відображає спрайт
    void setPosition(sf::Vector2f position); // Встановлює позицію спрайта
    void setScale(sf::Vector2f scale);       // Встановлює масштаб спрайта
    void addAnimationFrame(const sf::IntRect& frame); // Додає кадр до анімації
};
