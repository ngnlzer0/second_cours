#pragma once

#include"posittion.h"
#include"weapon.h"
class Unit: public posittion, public weapon
{
private:
	double HP;
public:

	int Get_HP() { return HP; }
	void Set_new_HP(double new_HP) { HP = new_HP; }
};

