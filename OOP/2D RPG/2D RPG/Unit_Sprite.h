#pragma once
#include"Includer.h"
#include"position.h"

class Unit_Sprite
{
private:
	sf::Sprite Unit_S;
	sf::Texture unit_texture;
	const std::string name_file_unit_texture;
	sf::Vector2f Size_unit_sprite;
public:
	Unit_Sprite(const std::string texture_file = "", sf::Vector2f pos = {}, sf::Vector2f size = {}, bool chois_rect = false, sf::IntRect Pos_texture = {0,0,0,0});

	sf::Sprite GUS() { return Unit_S; };

	//virtual void update(const float& delta_time) = 0;
	//virtual void render(sf::RenderTarget& target) = 0;
};

