#pragma once
#include"All_weapon/weapon/weapon.h"
#include"All_Armor/All_Armor.h"

template <typename W>
class Unit
{
private:
	std::unique_ptr<W> U_weapon;
	std::unique_ptr<Gloves> Gloves;
	double HP;
	int stamina;
public:

	double Get_HP() { return HP; }
	void Set_new_HP(double new_HP) { HP = new_HP; }
};

