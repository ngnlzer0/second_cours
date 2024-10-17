#include "Buttons.h"
#include<SFML/Graphics.hpp>

void Buttons::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(Background);
	target.draw(title);
}

Buttons::Buttons(const sf::Vector2f& position, const sf::Vector2f& Size, const std::string& title,
	const std::string font_m, const std::string name_text_file_un, sf::Vector2f Size_text_u, bool change_S_t,sf::IntRect Size_texture)
	:font_file(font_m), name_textuer_file(name_text_file_un),Size_text(Size_text)
{

	Background.setOrigin({ Size.x / 2, Size.y / 2 });
	Background.setPosition(position);
	Background.setSize(Size);

	if (change_S_t)
		texture.loadFromFile(name_textuer_file, Size_texture);
	else
		texture.loadFromFile(name_textuer_file);
	Background.setTexture(&texture);

	font.loadFromFile(font_file);
	this->title.setFont(font);
	this->title.setString(title);
	this->title.setOrigin(this->title.getLocalBounds().width / 2, this->title.getLocalBounds().height / 2);
	this->title.setPosition(position);
	this->title.setScale(Size_text_u);
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
