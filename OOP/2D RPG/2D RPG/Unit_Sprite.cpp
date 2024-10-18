#include "Unit_Sprite.h"

Unit_Sprite::Unit_Sprite(const std::string texture_file, sf::Vector2f pos, sf::Vector2f size)
	:name_file_unit_texture(texture_file),Size_unit_sprite(size)
{
	unit_texture.loadFromFile(name_file_unit_texture);
	Unit_S.setTexture(unit_texture);
	Unit_S.setPosition(pos);
	Unit_S.setScale(size);


}

void Unit_Sprite::update(const float& delta_time)
{
}

void Unit_Sprite::render(sf::RenderTarget& target)
{
}
