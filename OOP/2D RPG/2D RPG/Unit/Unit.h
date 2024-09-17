#pragma once
#include"All_weapon/weapon/weapon.h"
class Unit: public weapon
{
private:
	double HP;
public:

	double Get_HP() { return HP; }
	void Set_new_HP(double new_HP) { HP = new_HP; }
};

