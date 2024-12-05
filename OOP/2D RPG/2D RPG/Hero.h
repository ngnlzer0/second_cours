#pragma once

#include "Unit.h"
#include "Unit_sprite/Unit_Sprite.h"
#include <map>
#include "Unit_sprite/Animation/Animation.h" // Додайте цей заголовок, якщо він потрібен для використання Animation


class Hero : public Unit
{
private:

    Unit_Sprite hero_sprite;
    std::map<std::string, Animation> hero_animations;
    float speed;
    bool isMoving;
    sf::Vector2f direction;
    sf::Vector2f movement;

    enum class HeroState { Idle, Running, Attacking } state;
    Animation* currentAnim; // Додано для відстеження поточної анімації

    sf::Vector2f initialScale_h;

public:
    Hero();

    void move(sf::Vector2f offset);
    void update(float deltaTime);
    void handleInput(const sf::Event& event, const sf::RenderWindow& window); // Оновлено
    void processMovement(float deltaTime, const sf::RenderWindow& window); // Залежить від розмірів вікна
    void updateAnimation();
    void startAnimation(const std::string& animationName);

    void updateSpriteOrientation(float scaleX);

    Unit_Sprite* Get_sprite() { return &hero_sprite; }

};
