#pragma once

#include"Includer.h"

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

	sf::Text Ex_text;
	sf::Font font;

public:
	Main_menu();

	void Run_M();
	sf::RectangleShape& Get_Back_fon() { return Back_fon; };
	sf::RectangleShape& Get_Play() { return Play; };
	sf::RectangleShape& Get_Setting() { return Setting; };
	sf::RectangleShape& Get_Exit() { return Exit; };
	sf::Text& Get_Ex_text() { return Ex_text; };

	void Select_exit();
	void Deselect_exit();
	void Select_Play();
	void Deselete_Play();
	void select_Setting();
	void Deselect_Setting();
};

