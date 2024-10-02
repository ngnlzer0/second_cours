#include "weapon.h"
#include<iostream>
#include<time.h>

weapon::weapon(double g_damage, double g_weight, double g_block, double g_missing, int g_durability, weapon_type g_Type, bool random)
	:Type(g_Type), damage(g_damage), weight(g_weight),block(g_block),
	missing(g_missing), durability(g_durability)
{
	if (random)
	{
		srand(time(NULL));
		Type = static_cast<weapon_type>(rand()%5) ;
		damage = rand() % 25 + 5;
		weight = rand() % 15 + 5;
		block = rand() % 35 + 5;
		missing = rand() % 25 + 5;
		durability = rand() % 90 + 10;
	}
}



