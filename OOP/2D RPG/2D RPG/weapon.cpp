#include "weapon.h"
#include"Randomaizer.h"

const std::unordered_map<weapon_type, std::string> weapon::weaponTexturePaths = {
	{Sword, "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/other_elements/sword_01.png"},
	{Bow, "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/other_elements/bow_02.png"},
	{Sword_and_shield, "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/other_elements/shield_01.png"},
	{Staff, "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/other_elements/wand_01.png"}
};

weapon::weapon(int pos_x, int pos_y, double g_damage, double g_weight, double g_block, double g_missing, int g_durability, weapon_type g_Type, bool random)
	:BaseItem("weapon", 5.0), type(g_Type), damage(g_damage), weight(g_weight), block(g_block),
	missing(g_missing), durability(g_durability)
{
	if (random)
	{
		type = static_cast<weapon_type>(Genereta_int_random_number() %4) ;
		damage = Genereta_int_random_number() % 25 + 5;
		weight = Genereta_int_random_number() % 15 + 5;
		Set_weight_i(weight);
		block = Genereta_int_random_number() % 35 + 5;
		missing = Genereta_int_random_number() % 25 + 5;
		durability = Genereta_int_random_number() % 90 + 10;
	}

	std::string weapon_texture_path = weaponTexturePaths.at(type);

	weapon_button = new Buttons(sf::Vector2f(pos_x, pos_y), { 50, 50 }, weapon_texture_path, "",
		"C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/font/Gothical.ttf");

}



