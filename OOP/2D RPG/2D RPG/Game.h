#pragma once
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<list>
#include"Main_menu.h"

#include"Buttons.h"

class Game 
{
private:

	sf::Image window_icon;
	sf::VideoMode windowSize = { 1920,1080 };
	sf::String windowTitle = "2D RPG game";
	sf::RenderWindow window;

	Main_menu Main_Menu;

	sf::Font Mfont;

	Buttons Play;

	bool Main_menu_open = true;

	void HandleInput();
	void Update(float delta_Time);
	void Render();
public:
	Game();

	void Run();

};

