#pragma once

#include"weapon.h"
#include"Armor.h"
#include"potion.h"
#include"stamina_pot.h"
#include"position.h"

class cheast : virtual public position
{
public:
	weapon* ch_weapon;
	Armor* ch_armor;
	potion* ch_potion;
	stamina_pot* ch_stamina_pot;

	cheast(int num1 = 0,int num2 = 0);

	weapon* Get_weapon() { return ch_weapon; }
	Armor* Get_armro() { return ch_armor; }
	potion* Get_potion() { return ch_potion; }
	stamina_pot* Get_stamina_pot() { return ch_stamina_pot; }

};

