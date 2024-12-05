#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include "Animation/Animation.h"

class Buttons;

class Unit_Sprite {
private:
    sf::Sprite unit_sprite;
    std::string unit_name_texture;
    sf::Texture unit_texture;
    sf::Texture defaultTexture;   // Стандартна текстура
    sf::Vector2f position_sprite;

    std::map<std::string, Animation*> animations;
    Animation* currentAnimation;
    std::string idleAnimationName;

    sf::Texture* currentTexture; // Змінна для поточної текстури

    sf::Vector2f initialScale;

public:
    Unit_Sprite(const std::string& textureFile = "", sf::Vector2f pos = { 0, 0 }, bool fullPhoto = false, sf::IntRect size = { 0, 0, 0 ,0 });
    ~Unit_Sprite();

    void move(sf::Vector2f offset);                // Зміщення спрайта
    void update(float deltaTime);                  // Оновлення анімації
    void draw(sf::RenderWindow& window);           // Відображення спрайта
    void startAnimation(const std::string& name);  // Запуск анімації
    void addAnimation(const std::string& name, const Animation& animation); // Додавання анімації
    void handleEvent(const sf::Event& event);      // Обробка подій

    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);

    void setRotation(float angle);                // Встановлення обертання спрайта
    sf::Vector2f getScale() const { return initialScale; }
    void setScale(float x, float y);              // Встановлення масштабу спрайта

    void setFlipped(bool flipped);

    sf::FloatRect getLocalBounds() const {
        return unit_sprite.getLocalBounds();
    }
    void setOrigin(float x, float y) {
        unit_sprite.setOrigin(x, y);
    }

    Animation* getAnimation(const std::string& name);
    Animation* getCurrentAnimation() { return currentAnimation; };

    sf::FloatRect getGlobalBounds() const;

};