#pragma once

#include<SFML/Graphics.hpp>

namespace sf
{

}

class Buttons : public sf::Transformable, public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Text title;
	sf::Font font;
	sf::RectangleShape Background;
	sf::Texture texture;
	std::string name_text_file;

public:
	Buttons(const sf::Vector2f& position,const sf::Vector2f& Size, const std::string& title,const sf::Font font_m, const std::string name_text_file_up);
	Buttons() =  default;

	void Select();
	void Deselect();

	sf::FloatRect Get_global_bounds() const ;
};

