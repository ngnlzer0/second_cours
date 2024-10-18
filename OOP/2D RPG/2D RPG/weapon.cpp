#include "weapon.h"
#include"Randomaizer.h"

weapon::weapon(double g_damage, double g_weight, double g_block, double g_missing, int g_durability, weapon_type g_Type, bool random)
	:Type(g_Type), damage(g_damage), weight(g_weight),block(g_block),
	missing(g_missing), durability(g_durability)
{
	if (random)
	{
		Type = static_cast<weapon_type>(Genereta_int_random_number()%5) ;
		damage = Genereta_int_random_number() % 25 + 5;
		weight = Genereta_int_random_number() % 15 + 5;
		block = Genereta_int_random_number() % 35 + 5;
		missing = Genereta_int_random_number() % 25 + 5;
		durability = Genereta_int_random_number() % 90 + 10;
	}

	weapon_B = new Buttons({ 800,800 }, { 100,100 }, "", "",
		"C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/16x16 Assorted RPG Icons/weapons.png", {}, true, { 112,128,16,16 });
}



