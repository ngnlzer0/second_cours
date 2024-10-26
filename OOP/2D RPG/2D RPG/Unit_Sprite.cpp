#include "Unit_Sprite.h"

Unit_Sprite::Unit_Sprite(const std::string texture_file, sf::Vector2f pos, sf::Vector2f size, bool chois_rect, sf::IntRect Pos_texture)
	:name_file_unit_texture(texture_file),Size_unit_sprite(size)
{
	if (chois_rect)
		unit_texture.loadFromFile(name_file_unit_texture, Pos_texture);
	else
		unit_texture.loadFromFile(name_file_unit_texture);

	Unit_S.setTexture(unit_texture);
	Unit_S.setPosition(pos);
	Unit_S.setScale(size);

}

