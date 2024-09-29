#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include"Hero.h"

int main()
{
	Unit Hero(100, 90, 60, 35, 30,300);
	Unit Monstr;
	Unit Ogr;
	Monstr.attack_enemi(&Hero);
	Hero.inventar.add_potion(3);
	Hero.Healt_self();
	Hero.inventar.add_stamina_pot(5);

	weapon* Bow = new weapon;
	Armor* shoes = new Armor;
	
	Hero.Swap_weapon(Bow);
	Hero.Swap_armror(shoes);

	return 0;
}