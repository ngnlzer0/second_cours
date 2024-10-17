#pragma once
#include<list>
#include"Main_menu.h"

#include"Buttons.h"
#include"potion.h"
#include"weapon.h"

class Game 
{
private:

	sf::Image window_icon;
	sf::VideoMode windowSize = { 1920,1080 };
	sf::String windowTitle = "2D RPG game";
	sf::RenderWindow window;

	Main_menu Main_Menu;

	sf::Font Mfont;

	bool Main_menu_open = true;

	void HandleInput();
	void Update(float delta_Time);
	void Render();
public:
	Game();

	void Run();

};

