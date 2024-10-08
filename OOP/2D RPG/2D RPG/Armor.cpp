#include "Armor.h"
#include<iostream>
#include<time.h>

Armor::Armor(double g_weight, double g_block, double g_missing, int g_durability, Armor_type g_type, bool random)
	: type(g_type), weight(Set_weight(g_weight)), block(Set_block(g_block)),miss(Set_missing(g_missing)),durability(Set_durability(g_durability))
{
	if (random)
	{
		std::srand(std::time(NULL));
		type = static_cast<Armor_type>(rand() % 5);
		weight = rand() % 30 + 10;
		block = rand() % 40 + 10;
		miss = rand() % 20 + 5;
		durability = rand() % 200 + 50;
	}
}
