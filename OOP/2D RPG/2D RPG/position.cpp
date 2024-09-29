#include "position.h"

position::position(int new_x, int new_y)
	:x(new_x < MAX_X ? new_x : MAX_X),y(new_y < MAX_Y ? new_y : MAX_Y)
{

}

void position::Set_new_X(int num)
{
	if (num > 0 && num < MAX_X)
		x = num;
	else if (num <= 0)
		x = 0;
	else
		x = MAX_X;
}

void position::Set_new_Y(int num)
{
	if (num > 0 && num < MAX_Y)
		y = num;
	else if (num <= 0)
		y = 0;
	else
		y = MAX_Y;
}
