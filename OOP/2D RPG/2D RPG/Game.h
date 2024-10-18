#pragma once
#include<list>
#include"Main_menu.h"

#include"Includer.h"
#include"Unit_Sprite.h"

class Game 
{
private:

	sf::Image window_icon;
	sf::VideoMode windowSize = {WIDHT_WINDOW,HIGHT_WINDOW};
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

