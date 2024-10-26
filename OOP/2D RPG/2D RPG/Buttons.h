#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>  

class Buttons : public sf::Drawable, public sf::Transformable
{
private:
    friend class sf::Drawable;

    sf::Text title;
    sf::Font font;
    sf::RectangleShape Background;
    sf::Texture texture;
    std::string font_file;
    std::string name_textuer_file;

    // Приватний метод draw з правильними параметрами
    
public:
    Buttons(const sf::Vector2f& position = {0,0}, const sf::Vector2f& size = {1,1},
        const std::string& texturePath = "",const std::string& titleText = "",
        const std::string& fontPath = "", const sf::Vector2f& textScale = {1,1},
        bool useSubRect = false, const sf::IntRect& textureRect = sf::IntRect() = {0,0,100,100});

    Buttons();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void Select(sf::Color color);
    void Deselect(sf::Color color);
    sf::FloatRect GetGlobalBounds() const;
};



