#pragma once
#include"Unit.h"
class Hero : virtual public Unit
{
private:
	int money;
public:
	Hero(const double g_max_hp = 150, const int g_max_stamina = 100, int g_speed = 50, double g_block = 40, double g_miss = 25, int g_money = 100);
};

