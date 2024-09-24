#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include"Unit/Unit.h"

int main()
{

	const sf::VideoMode Window_SIZE(1920, 1080);
	sf::RenderWindow window(Window_SIZE, "The 2D RPG Game");

	sf::Image icon;
	icon.loadFromFile("C:\Git.repos\second_cours\OOP\2D RPG\Resources\win_icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	while (true)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

		}
	}

	weapon Sword1( 3.4, 11.0, 15.0, 23.44,11);
	weapon Bow(Staff, -3.0, 11.0, -23.4,12.0,50);
	
	Show_weapon(Sword1);
	std::cout<<std::endl;
	Show_weapon(Bow);

	return 0;
}