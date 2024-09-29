#pragma once
class potion
{
private:
	int regeneration_hp;
	double weight;
public:
	potion(int g_regeneration_hp = 10,double g_weight = 0.9);
	double Get_weight_potion() { return weight; }
	int Get_regeneration_hp() { return regeneration_hp; }
};

