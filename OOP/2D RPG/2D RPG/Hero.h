#pragma once

#include "Unit.h"
#include "Unit_sprite/Unit_Sprite.h"
#include <map>

class Hero : public Unit
{
private:
    Unit_Sprite hero_sprite;
    static std::map<std::string, Animation> hero_animations;
    float speed;
    bool isMoving;
    sf::Vector2f direction;
    sf::Vector2f movement;

    enum class HeroState { Idle, Running, Attacking } state;

public:
    Hero();

    void move(sf::Vector2f offset);
    void update(float deltaTime);
    void handleInput(const sf::Event& event);
    void processMovement(float deltaTime);
    void updateAnimation();

    void updateSpriteOrientation(float scaleX);
    void handleInput()
    {
        processMovement(0.0f); // Рух через клавіші WASD
    }

    Unit_Sprite* Get_sprite() { return &hero_sprite; }
};
