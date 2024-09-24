#include "Gloves.h"

Gloves::Gloves(double g_weight, double g_block, double g_missing, int g_durability, double g_attack_speed, int g_chance_add_attack,bool type[num_weapon_type])
	:Armor(g_weight, g_block, g_missing, g_durability), attack_speed(g_attack_speed), chance_add_attack(g_attack_speed)
{
	for (int i = 0; i < num_weapon_type; i++)
		Set_avaliable_weapon(type[i], i);
}

