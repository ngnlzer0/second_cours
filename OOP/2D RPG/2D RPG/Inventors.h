#pragma once
#include<vector>
#include"potion.h"
class Inventors : public potion
{
private:
	double weight_inventors;
	int number_potion;
public:
	Inventors(double g_weight_inventors = 0.0, int g_number_potion = 0, bool random = 1);

	double Get_weight_inventors() { return weight_inventors; }
	void Set_new_weight_invontors(double g_weight_inventors) { weight_inventors = g_weight_inventors; }

	int Get_number_potion() { return number_potion; }
	void Set_new_number_potion(int new_number) { number_potion = new_number; }

	
	void add_potion(int num) { Set_new_number_potion(Get_number_potion() + num); Set_new_weight_invontors(Get_weight_inventors() + static_cast<double>(num * 1)); }
	void dell_potion(int num) { Set_new_number_potion(Get_number_potion() - num); Set_new_weight_invontors(Get_weight_inventors() - static_cast<double>(num * 1)); }

	bool Get_potion() { return Get_number_potion() > 0 ? true : false; }

};

