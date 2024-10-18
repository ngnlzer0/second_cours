#include "Armor.h"
#include"Randomaizer.h"

Armor::Armor(double g_weight, double g_block, double g_missing, int g_durability, Armor_type g_type, bool random)
	: type(g_type), weight(Set_weight(g_weight)), block(Set_block(g_block)),miss(Set_missing(g_missing)),durability(Set_durability(g_durability))
{
	if (random)
	{
		type = static_cast<Armor_type>(Genereta_int_random_number() % 5);
		weight = Genereta_int_random_number() % 30 + 10;
		block = Genereta_int_random_number() % 40 + 10;
		miss = Genereta_int_random_number() % 20 + 5;
		durability = Genereta_int_random_number() % 200 + 50;
	}
}
