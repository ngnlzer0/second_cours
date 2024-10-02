#pragma once
#include"potion.h"
#include"stamina_pot.h"
class Inventors : public potion, public stamina_pot
{
private:
	double weight_inventors;
public:
	Inventors(double g_weight_inventors = 0.0);

	double Get_weight_inventors() { return weight_inventors; }
	void Set_new_weight_invontors(double g_weight_inventors) { weight_inventors = g_weight_inventors; }
	
	void add_potion(int num);
	void dell_potion(int num);

	void add_stamina_pot(int number);
	void dell_stamina_pot(int number);
};

