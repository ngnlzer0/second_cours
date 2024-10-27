#pragma once
#include<list>
#include"Main_menu.h"

#include"Includer.h"
#include"Unit.h"
#include"Armor.h"

#include"WFC/WFCMapGenerator.h"
#include"WFC/TileMap.h"

class Game 
{
private:

	sf::Image window_icon;
	sf::VideoMode windowSize = {WIDHT_WINDOW,HIGHT_WINDOW};
	sf::String windowTitle = "2D RPG game";

	sf::RenderWindow window;
	Main_menu Main_Menu; // Ваше меню
	TileMap tileMap; // Ваша карта тайлів
	WFCMapGenerator wfcMapGenerator; // Ваш генератор карти
	bool Main_menu_open = true; // Стан меню
	bool isGameActive = false; // Стан гри

	sf::Font Mfont;

	Armor* head;
	weapon* sword;
	stamina_pot* stamina;
	potion* healt;

	void HandleInput();
	void Update(float delta_Time);
	void Render();
public:
	Game();

	void Run();

};

