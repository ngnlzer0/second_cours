#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include<string>

class Animation
{
private:
    std::vector<sf::IntRect> frames; // Кадри анімації
    const std::string name_texture_animation;
    sf::Texture texture_animation;
    float duration;                   // Загальний час анімації
    float elapsedTime;                // Час, що пройшов від початку анімації
    float frameTime;
    int currentFrame;                 // Поточний кадр
    bool finished;

public:
    Animation(const std::string name_file = " ",int number_frames = 0,sf::IntRect parametrs_frame = {}, float duration = 1.0f);

    void update(float deltaTime);
    void reset();
    sf::Texture* getTexture() { return &texture_animation; };
    sf::IntRect getCurrentFrame() const { return frames[currentFrame]; };
    bool isFinished() const { return finished; };

};

