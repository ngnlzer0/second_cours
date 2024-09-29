#include "Inventors.h"
#include<iostream>
#include<time.h>

Inventors::Inventors(double g_weight_inventors)
	:weight_inventors(g_weight_inventors)
{

}

void Inventors::add_potion(int num)
{
	potion::add_potion(num);
	Set_new_weight_invontors(Get_weight_inventors() + static_cast<double>(num * Get_weight_potion()));
}

void Inventors::dell_potion(int num)
{
	potion::dell_potion(num);
	Set_new_weight_invontors(Get_weight_inventors() - static_cast<double>(num * Get_weight_potion()));
}

void Inventors::add_stamina_pot(int number)
{
	stamina_pot::add_stamina_pot(number);
	Set_new_weight_invontors(Get_weight_inventors() + static_cast<double>(number * Get_weight_stamina_pot()));
}

void Inventors::dell_stamina_pot(int number)
{
	stamina_pot::dell_stamina_pot(number);
	Set_new_weight_invontors(Get_weight_inventors() - static_cast<double>(number * Get_weight_stamina_pot())); 
}

