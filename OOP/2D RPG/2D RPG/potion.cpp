#include "potion.h"

potion::potion(int g_regeneration_hp, double g_weight)
	:regeneration_hp(10),weight(1.0),number_potion(0),All_Weight_potion(0)
{
	Potion_B = new Buttons({ 600,600 }, { 50,50 }, "", "",
		"C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/16x16 Assorted RPG Icons/potions.png",{},true,{48,96,16,16});
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
