#include "Inventors.h"
#include<iostream>
#include<time.h>

Inventors::Inventors(double g_weight_inventors)
	:weight_inventors(g_weight_inventors)
{

}

void Inventors::add_potion(int num)
{
	Set_new_number_potion(Get_number_potion() + num);
	Set_new_weight_invontors(Get_weight_inventors() + static_cast<double>(num * Get_weight_potion()));
	Set_new_All_weight_potion(Get_All_weight_potion() + num * Get_weight_potion());
}

void Inventors::dell_potion(int num)
{
	Set_new_number_potion(Get_number_potion() - num); 
	Set_new_weight_invontors(Get_weight_inventors() - static_cast<double>(num * Get_weight_potion()));
	Set_new_All_weight_potion(Get_All_weight_potion() - num * Get_weight_potion());
}

void Inventors::add_stamina_pot(int number)
{
	Set_new_number_stamina_pot(Get_number_stamina_pot() + number);
	Set_new_weight_invontors(Get_weight_inventors() + static_cast<double>(number * Get_weight_stamina_pot()));
	Set_new_All_weight_stamina_pot(Get_All_weight_stamina_pot() + number * Get_weight_stamina_pot());
}

void Inventors::dell_stamina_pot(int number)
{
	Set_new_number_stamina_pot(Get_number_stamina_pot() - number);
	Set_new_weight_invontors(Get_weight_inventors() - static_cast<double>(number * Get_weight_stamina_pot()));
	Set_new_All_weight_stamina_pot(Get_All_weight_stamina_pot() - number * Get_weight_stamina_pot());
}

