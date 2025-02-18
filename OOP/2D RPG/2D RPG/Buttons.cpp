#include "Buttons.h"
#include <iostream>

// Конструктор Buttons (уже наданий)
Buttons::Buttons(const sf::Vector2f& position, const sf::Vector2f& size,
    const std::string& texturePath, const std::string& titleText,
    const std::string& fontPath, const sf::Vector2f& textScale,
    bool useSubRect, const sf::IntRect& textureRect)
    : font_file(fontPath), name_textuer_file(texturePath)
{
    // Установка основних параметрів
    Background.setOrigin(size.x / 2, size.y / 2);
    Background.setPosition(position);
    Background.setSize(size);

    // Завантаження текстури
    std::cout << "Loading texture from: " << name_textuer_file << std::endl;
    if (!texture.loadFromFile(name_textuer_file, useSubRect ? textureRect : sf::IntRect())) {
       throw std::runtime_error("Failed to load texture from file: " + name_textuer_file);
    }
    Background.setTexture(&texture);

    //Завантаження шрифту
    if (!font.loadFromFile(font_file)) {
        throw std::runtime_error("Failed to load font from file: " + font_file);
    }
    title.setFont(font);
    title.setString(titleText);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(position);
    title.setScale(textScale);
}

// Реалізація функції draw
void Buttons::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(Background, states);
    target.draw(title, states);
}

// Реалізація методу Select
void Buttons::Select(sf::Color color)
{
    Background.setFillColor(color); // Зміна кольору фону для позначення вибору
}

// Реалізація методу Deselect
void Buttons::Deselect(sf::Color color)
{
    Background.setFillColor(color); // Зміна кольору фону для зняття вибору
}

// Реалізація методу GetGlobalBounds
sf::FloatRect Buttons::GetGlobalBounds() const
{
    return Background.getGlobalBounds(); // Повернення меж кнопки
}
