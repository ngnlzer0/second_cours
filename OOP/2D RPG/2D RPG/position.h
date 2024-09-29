#pragma once

const int MAX_X = 60;
const int MAX_Y = 45;

class position
{
private:
	int x;
	int y;
public:
	position(int new_x, int new_y);

	int Get_X() { return x; }
	int Get_Y() { return y; }

	void Set_new_X(int num);
	void Set_new_Y(int num);
};

