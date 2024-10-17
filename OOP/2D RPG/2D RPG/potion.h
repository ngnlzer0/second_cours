#pragma once
#include"Buttons.h"
class potion
{
private:
	int number_potion;
	double All_Weight_potion;
	const int regeneration_hp;
	const double weight;
	Buttons* Potion_B;
public:
	potion(int g_regeneration_hp = 10,double g_weight =1.0);
	double Get_weight_potion() { return weight; }
	int Get_regeneration_hp() { return regeneration_hp; }
	int Get_number_potion() { return number_potion; }
	void Set_new_number_potion(int new_number) { number_potion = new_number; }
	double Get_All_weight_potion() { return All_Weight_potion; }
	void Set_new_All_weight_potion(double new_num) { All_Weight_potion = new_num; }

	void add_potion(int number);
	void dell_potion(int number);

	Buttons* Get_Buttons() { return Potion_B; }
};

