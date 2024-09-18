#include "weapon.h"

weapon::weapon(weapon_type g_Type, double g_damage, double g_weight, double g_block, double g_missing, int g_durability)
	:Type(g_Type), damage(Set_damage(g_damage)), weight(Set_weight(g_weight)), block(Set_block(g_block)),
	missing(Set_missing(g_missing)), durability(Set_durability(g_durability))
{}

void Show_weapon(weapon weapon)
{
	std::cout << " Damage your weapon = " << weapon.Get_damage() << std::endl;
	std::cout << " Weight your weapon = " << weapon.Get_weight() << std::endl;
	std::cout << " Block your weapon = " << weapon.Get_block() << std::endl;
	std::cout << " missing your weapon = " << weapon.Get_missing() << std::endl;
	std::cout << " durability your weapon = " << weapon.Get_durability() << std::endl;
}

/*weapon::weapon(weapon_type g_Type, double g_damage, double g_weight, double g_block, double g_missing, int g_durability)
	:Type(g_Type), damage(Set_damage(g_damage)), weight(Set_weight(g_weight)), block(Set_block(g_block)),
	 missing(Set_missing(g_missing)), durability(Set_durability(g_durability))
{}

weapon::weapon(weapon_type g_Type, double  g_damage, double  g_weight, double  g_block, double  g_missing, int g_durability)
	:Type(g_Type), damage(Set_damage(g_damage)), weight(Set_weight(g_weight)), block(Set_block(g_block)),
	missing(Set_missing(g_missing)), durability(Set_durability(g_durability))
{}*/
