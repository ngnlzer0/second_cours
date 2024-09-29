#include "cheast.h"
#include<iostream>
#include<time.h>

cheast::cheast(int num1, int num2)
	:position(num1,num2),ch_armor(NULL),ch_potion(NULL),ch_stamina_pot(NULL),ch_weapon(NULL)
{
	srand(time(NULL));
	int lower_rand = 1;
	if (rand() % 100 > 30 * lower_rand)
	{
		ch_potion = new potion;
		lower_rand++;
	}
	if (rand() % 100 > 35 * lower_rand)
	{
		ch_stamina_pot = new stamina_pot;
		lower_rand++;
	}
	if (rand() % 10 > 3 * lower_rand)
	{
		ch_weapon = new weapon;
		lower_rand++;
	}
	if (rand() % 10 > 3 * lower_rand)
	{
		ch_armor = new Armor;
	}
}
