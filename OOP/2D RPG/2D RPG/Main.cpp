#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include"Hero.h"

int main()
{
	Hero Hero(100, 90, 60, 35, 30,300);
	Unit Monstr;
	Monstr.attack_enemi(&Hero);
	return 0;
}