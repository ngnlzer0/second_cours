#pragma once
#include <SFML/Graphics.hpp>
#include <stdexcept>

class Animation {
private:
    std::string name;
    sf::Texture texture;
    std::string name_texture;
    sf::IntRect frames[10];  // Статичний масив для 100 кадрів
    int currentFrame;
    float duration;
    float elapsedTime;
    int frameCount;

public:
    Animation(const std::string& textureFile = "", int frameCount = 1, sf::IntRect frameSize = { 0, 0, 0, 0 }, const std::string& animName = " ");
    Animation(const Animation& other);              // Конструктор копіювання
    Animation& operator=(const Animation& other);   // Оператор присвоєння

    void update(float deltaTime);   // Оновлення кадру анімації
    void reset();                   // Скидання анімації до першого кадру
    bool isFinished() const;        // Перевірка, чи завершилась анімація
    sf::IntRect getCurrentFrame() const; // Отримання поточного кадру
    sf::Texture* getTexture(); // Отримання текстури анімації

    std::string getName() const { return name; }
};

