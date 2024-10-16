#include "Buttons.h"
#include<SFML/Graphics.hpp>

void Buttons::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(Background);
	//target.draw(title);
}

Buttons::Buttons(const sf::Vector2f& position, const sf::Vector2f& Size, const std::string& title,const sf::Font font_m, const std::string name_text_file_un)
{
	const std::string font_or = "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/font/Gothical.ttf";
	this->name_text_file = name_text_file_un;

	Background.setOrigin({ Size.x / 2, Size.y / 2 });
	Background.setPosition(position);
	Background.setSize(Size);
	Background.setOutlineColor(sf::Color::Black);

	texture.loadFromFile(name_text_file);
	Background.setTexture(&texture);
	Background.setOutlineThickness(2);
	Background.setTexture(&texture);

	this->title.setFont(font_m);
	this->title.setString(title);
	this->title.setPosition(position.x + 50, position.y + 50);
}

void Buttons::Select()
{
	Background.setFillColor(sf::Color(0, 200, 0));
}

void Buttons::Deselect()
{
	Background.setFillColor(sf::Color(100, 100, 100));
}

sf::FloatRect Buttons::Get_global_bounds() const
{
	return Background.getGlobalBounds();
}
