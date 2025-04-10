﻿#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>

class Animation {
private:
    std::string name;
    sf::Texture texture;
    const std::string name_texture;
    std::vector<sf::IntRect> frames;
    int currentFrame;
    float duration;
    float elapsedTime;
    int frameCount;

    bool isLooping;

public:
    Animation(const std::string& textureFile = "", int frameCount = 1, sf::IntRect frameSize = { 0, 0, 0, 0 }, const std::string& animName = " ", bool looping = false);
    Animation(const Animation& other);              // Конструктор копіювання
    Animation& operator=(const Animation& other);   // Оператор присвоєння

    void update(float deltaTime);   // Оновлення кадру анімації
    void reset();                   // Скидання анімації до першого кадру
    sf::IntRect getCurrentFrame() const; // Отримання поточного кадру
    sf::Texture* getTexture(); // Отримання текстури анімації

    std::string getName() const { return name; }

    bool isFinished() const {
        return !isLooping && (currentFrame == frames.size() - 1);
    }

};

