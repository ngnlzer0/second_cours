#include "potion.h"

potion::potion(float pos_x, float pos_y, int g_regeneration_hp, double g_weight)
	:BaseItem("", 0.9,true, { 48, 96, 16, 16 }),
	regeneration_hp(10), weight(1.0), number_potion(0), All_Weight_potion(0), Potion_sprite(sf::Vector2f{pos_x,pos_y}, {30,30},
		"C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/16x16 Assorted RPG Icons/potions.png", "", FONT, {}, true, { 48,96,16,16 })
{
	setNewTexture("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/16x16 Assorted RPG Icons/potions.png", true, { 48,96,16,16 });
	set_Weight_i(1.0);
}

void potion::add_potion(int number)
{
	Set_new_number_potion(Get_number_potion() + number);
	Set_new_All_weight_potion(Get_All_weight_potion() + number * Get_weight_potion());
}

void potion::dell_potion(int number)
{
	Set_new_number_potion(Get_number_potion() - number);
	Set_new_All_weight_potion(Get_All_weight_potion() - number * Get_weight_potion());
}
