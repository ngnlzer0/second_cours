#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include"Unit.h"

int main()
{
	Unit hero;
	Unit* Monstr = new Unit;
	Unit Ogr;
	hero.inventar.add_potion(3);
	hero.Healt_self();
	hero.inventar.add_stamina_pot(5);
	Monstr->inventar.add_potion(7);
	Monstr->inventar.add_stamina_pot(5);

	Fight(&hero, Monstr);

	std::cout << "end program\n";
	return 0;
}