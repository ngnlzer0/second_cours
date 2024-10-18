#pragma once

#include<SFML/System/Vector2.hpp>

const int MAX_X = 1920;
const int MAX_Y = 1080;

class position
{
private:
	sf::Vector2i Position;
public:
	position(int new_x, int new_y);
	position(sf::Vector2i vec);
	position() = default;

	int Get_X() { return Position.x; }
	int Get_Y() { return Position.y; }

	void Set_new_X(int num);
	void Set_new_Y(int num);
};

