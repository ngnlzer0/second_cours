#include "stamina_pot.h"

stamina_pot::stamina_pot(float pos_x,float pos_y,int g_regeneration_stamina, double g_weight_s)
	:BaseItem("Stamina_pot",1.1), regeneration_stamina(g_regeneration_stamina), weight_s(g_weight_s), number_stamina_pot(0), All_Weight_stamina_pot(0.0),
	stamina_potion_sprite(sf::Vector2f{pos_x,pos_y},{30,30}, "C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/other_elements/mana_potion.png","",FONT)
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
