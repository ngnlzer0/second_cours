#include "Unit.h"

Unit::Unit(const double g_max_hp, const int g_max_stamina,int g_speed, double g_block, double g_miss)
	:c_weapon(weapon()), c_armor(Armor()), max_HP(g_max_hp),max_stamina(g_max_stamina),HP(g_max_hp),stamina(g_max_stamina),speed(g_speed),
	block(g_block),miss(g_miss)
{

}

void Unit::received_damage(double minus_damage)
{
	HP -= minus_damage;
	if (HP <= 0)
		this->~Unit();
}

void Unit::attack_enemi(Unit* enemi)
{
	enemi->received_damage(this->c_weapon.Get_damage() * ((100 - enemi->Get_block()) / 100));
	stamina = static_cast<int>(stamina - stamina / 12);
}

