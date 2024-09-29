#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include"Hero.h"

int main()
{
	Hero Hero(100, 90, 60, 35, 30,300);
	Unit Monstr;
	Monstr.attack_enemi(&Hero);
	Hero.inventar.add_potion(3);
	Hero.Healt_self();
	
	Hero.Swap_weapon(*weapon());

	return 0;
}