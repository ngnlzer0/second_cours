#include "Armor.h"
#include "Randomaizer.h"
#include<iostream>

const std::unordered_map<Armor_type, std::string> Armor::armorTexturePaths = {
	{helmet, "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/other_elements/headgear_01.png"},
	{jacket, "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/other_elements/iron_armor.png"},
	{gloves, "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/other_elements/leather_glove.png"},
	{ring,   "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/other_elements/ring_02.png"},
	{shoes,  "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/other_elements/boots_02.png"}
};

Armor::Armor(int pos_x, int pos_y, double g_weight, double g_block, double g_missing, int g_durability, Armor_type g_type, bool random)
	: type(g_type), weight(Set_weight(g_weight)), block(Set_block(g_block)), miss(Set_missing(g_missing)), durability(Set_durability(g_durability))
{
	
	// Якщо увімкнено випадкове генерування, генеруємо випадкові значення
	if (random)
	{
		type = static_cast<Armor_type>(Genereta_int_random_number() % 5);
		weight = Genereta_int_random_number() % 30 + 10;
		block = Genereta_int_random_number() % 40 + 10;
		miss = Genereta_int_random_number() % 20 + 5;
		durability = Genereta_int_random_number() % 200 + 50;
	}

	std::string armor_texture_path = armorTexturePaths.at(type);

	armor_button = new Buttons(sf::Vector2f(pos_x, pos_y), { 50, 50 }, armor_texture_path, "",
		"C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/font/Gothical.ttf");
}
