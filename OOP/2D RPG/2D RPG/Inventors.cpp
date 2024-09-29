#include "Inventors.h"
#include<iostream>
#include<time.h>

Inventors::Inventors(double g_weight_inventors, int g_number_potion,bool random)
	:weight_inventors(g_weight_inventors),number_potion(g_weight_inventors)
{
	if (random)
	{
		srand(time(NULL));
		number_potion = rand() % 5;
		weight_inventors = Get_number_potion() * 1.0;
	}
}
