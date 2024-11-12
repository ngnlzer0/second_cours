#pragma once
#include"Animation/Animation.h"
#include<iostream>

class Unit_Sprite 
{
private:
	sf::Sprite unit_sprite;
	sf::Texture unit_texture;
    sf::Texture* currentTexture;
	const std::string name_unit_texture;
	sf::Vector2f position_sprite;

    std::map<std::string, Animation> animations; // Набір анімацій
    Animation* currentAnimation;                 // Поточна анімація
    std::string idleAnimationName = "idle";

public:
	Unit_Sprite(const std::string name_file = "", sf::Vector2f pos = {0,0}, bool full_photo = false, sf::IntRect Size = {0,0,0,0});

    void setPosition(sf::Vector2f pos) { unit_sprite.setPosition(pos); };
    void move(sf::Vector2f offset);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) { window.draw(unit_sprite); };

    // Робота з анімаціями
    void startAnimation(const std::string& name);
    void handleEvent(const sf::Event& event); // Обробка подій

};
