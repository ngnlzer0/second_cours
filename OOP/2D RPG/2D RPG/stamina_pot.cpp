#include "stamina_pot.h"

stamina_pot::stamina_pot(int g_regeneration_stamina, double g_weight_s)
	:regeneration_stamina(g_regeneration_stamina),weight_s(g_weight_s),number_stamina_pot(0),All_Weight_stamina_pot(0.0)
{
}

void stamina_pot::add_stamina_pot(int number)
{
	Set_new_number_stamina_pot(Get_number_stamina_pot() + number);
	Set_new_All_weight_stamina_pot(Get_All_weight_stamina_pot() + number * Get_weight_stamina_pot());
}

void stamina_pot::dell_stamina_pot(int number)
{
	Set_new_number_stamina_pot(Get_number_stamina_pot() - number);
	Set_new_All_weight_stamina_pot(Get_All_weight_stamina_pot() - number * Get_weight_stamina_pot());
}
