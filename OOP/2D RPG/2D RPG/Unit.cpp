#include "Unit.h"
#include<iostream>
#include<time.h>

Unit::Unit(const double max_weight, const double g_max_hp, const int g_max_stamina,int g_speed, double g_block, double g_miss)
	:c_weapon(*weapon()), c_armor(*Armor()),max_weight(max_weight), max_HP(g_max_hp),max_stamina(g_max_stamina),cur_weight(max_weight),
	HP(g_max_hp),stamina(g_max_stamina),speed(g_speed),block(g_block),miss(g_miss)
{
	cur_weight -= c_armor->Get_weight();
	cur_weight -= c_weapon->Get_weight();
}

void Unit::received_damage(double minus_damage)
{
	srand(time(NULL));
	if (rand() % 2 == 1)
		c_armor->Set_durability(c_armor->Get_durability() - 1);
	HP -= minus_damage;
	if (HP <= 0)
		this->~Unit();
}

void Unit::attack_enemi(Unit* enemi)
{
	enemi->received_damage(this->Get_weapon()->Get_damage() * ((100 - enemi->Get_block()) / 100));
	srand(time(NULL));
	if (rand() % 2 == 1)
		c_weapon->Set_durability(c_weapon->Get_durability() - 1);
	stamina = static_cast<int>(stamina - stamina / 12);
}

void Unit::Healt_self()
{
	if (inventar.Get_number_potion() > 0)
	{
		this->Set_new_HP(Get_HP() + inventar.Get_regeneration_hp());
		inventar.dell_potion(1);
	}
}

void Unit::Swap_weapon(weapon* other)
{
	weapon* temp = Get_weapon();
	this->Set_new_weapon(other);
	other = temp;
}

void Unit::Swap_armror(Armor* other)
{
	Armor* temp = this->Get_armor();
	this->Set_new_armor(other);

}


