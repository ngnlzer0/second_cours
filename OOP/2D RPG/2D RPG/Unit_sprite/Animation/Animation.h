#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Animation {
private:
    std::vector<sf::IntRect> frames; // Вектор кадрів анімації
    float duration;                   // Час між кадрами
    float elapsedTime;               // Час, що пройшов з останнього оновлення
    size_t currentFrame;             // Поточний кадр

public:
    Animation(float duration);

    void addFrame(const sf::IntRect& frame); // Додає кадр до анімації
    void update(float deltaTime);             // Оновлює анімацію
    sf::IntRect getCurrentFrame() const;      // Повертає поточний кадр
};


