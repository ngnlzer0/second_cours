#pragma once

#include<SFML/Graphics.hpp>

class Buttons : public sf::Transformable, public sf::Drawable
{
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Text title;
	const std::string font_file;
	sf::Font font;
	sf::RectangleShape Background;
	sf::Texture texture;
	const std::string name_textuer_file;

	int Size_text;

public:
	Buttons(const sf::Vector2f& position,const sf::Vector2f& Size, const std::string& title,
		const std::string font_m, const std::string name_text_file_up,sf::Vector2f Size_text_u = {1,1},
		bool change_S_t = false,sf::IntRect Size_texture = {0,0,0,0});
	Buttons() =  default;

	void Select(sf::Color g_color);
	void Deselect(sf::Color g_color);

	sf::FloatRect Get_global_bounds() const ;
};

