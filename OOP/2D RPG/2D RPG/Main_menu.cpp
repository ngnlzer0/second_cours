#include "Main_menu.h"

Main_menu::Main_menu()
{
	texture_back_fon.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/background_2.png");
	Back_fon.setPosition({ 0,0 });
	Back_fon.setSize({ 1920,980 });
	Back_fon.setTexture(&texture_back_fon);

	Play_texture.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/buttons/Buttons/Rect/PlayIcon/Default.png");
	Setting_texture.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/buttons/Buttons/Square/Levels/Default.png");
	Exit_texture.loadFromFile("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/buttons/Button/Rect/Default.png");

	Play.setTexture(&Play_texture);
	Setting.setTexture(&Setting_texture);
	Exit.setTexture(&Exit_texture);

	sf::Vector2f Size = { 200,200 };
	sf::Vector2f Midle_window_point = {960,550};
	Play.setSize(Size);
	Setting.setSize(Size);
	Exit.setSize(Size);
	Play.setPosition(Midle_window_point.x, Midle_window_point.y - 250);
	Setting.setPosition(Midle_window_point);
	Exit.setPosition(Midle_window_point.x, Midle_window_point.y + 250);
	Play.setOrigin(100, 100);
	Setting.setOrigin(100, 100);
	Exit.setOrigin(100, 100);
}


