#pragma once

#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

class Main_menu
{
private:
	sf::RectangleShape Back_fon;
	sf::RectangleShape Play;
	sf::RectangleShape Setting;
	sf::RectangleShape Exit;

	sf::Texture texture_back_fon;
	sf::Texture Play_texture;
	sf::Texture Setting_texture;
	sf::Texture Exit_texture;

public:
	Main_menu();

	void Run_M();
	sf::RectangleShape& Get_Back_fon() { return Back_fon; };
	sf::RectangleShape& Get_Play() { return Play; };
	sf::RectangleShape& Get_Setting() { return Setting; };
	sf::RectangleShape& Get_Exit() { return Exit; };
};
