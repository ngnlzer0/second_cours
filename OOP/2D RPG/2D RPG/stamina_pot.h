#pragma once
#include"Includer.h"
class stamina_pot
{
private:
	Buttons stamina_potion_sprite;

	int number_stamina_pot;
	double All_Weight_stamina_pot;
	const int regeneration_stamina;
	const double weight_s;
public:
	stamina_pot(float pos_x=0,float pos_y=0,int g_regeneration_stamina = 10, double g_weight_s = 1.0);
	double Get_weight_stamina_pot() { return weight_s; }
	int Get_regeneration_stamina() { return regeneration_stamina; }
	int Get_number_stamina_pot() { return number_stamina_pot; }
	void Set_new_number_stamina_pot(int new_number) { number_stamina_pot = new_number; }
	double Get_All_weight_stamina_pot() { return All_Weight_stamina_pot; }
	void Set_new_All_weight_stamina_pot(double new_num) { All_Weight_stamina_pot = new_num; }

	void add_stamina_pot(int number);
	void dell_stamina_pot(int number);

	Buttons& Get_buttons() { return stamina_potion_sprite; }
};

