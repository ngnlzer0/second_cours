#include "position.h"

position::position(int new_x, int new_y)
	:Position(new_x,new_y)
{

}

position::position(sf::Vector2i vec)
	:Position(vec)
{
}

void position::Set_new_X(int num)
{
	if (num > 0 && num < MAX_X)
		Position.x = num;
	else if (num <= 0)
		Position.x = 0;
	else
		Position.x = MAX_X;
}

void position::Set_new_Y(int num)
{
	if (num > 0 && num < MAX_Y)
		Position.y = num;
	else if (num <= 0)
		Position.y = 0;
	else
		Position.y = MAX_Y;
}
