#pragma once
#include"Includer.h"
#include"BaseItem.h"

class potion : public BaseItem
{
private:
	int number_potion;
	double All_Weight_potion;
	const int regeneration_hp;
	const double weight;
	Buttons Potion_sprite;
public:
	potion(float pos_x = 0,float pos_y = 0,int g_regeneration_hp = 10,double g_weight =1.0);
	double Get_weight_potion() { return weight; }
	int Get_regeneration_hp() { return regeneration_hp; }
	int Get_number_potion() { return number_potion; }
	void Set_new_number_potion(int new_number) { number_potion = new_number; }
	double Get_All_weight_potion() { return All_Weight_potion; }
	void Set_new_All_weight_potion(double new_num) { All_Weight_potion = new_num; }

	void add_potion(int number);
	void dell_potion(int number);

	Buttons& Get_Buttons() { return Potion_sprite; }
};

