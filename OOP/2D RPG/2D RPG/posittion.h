#pragma once
class posittion
{
private:
	int x;
	int y;
public:

	int Get_posittion_x() {return x;}
	int Get_posittion_y() {return y;}

	void Set_new_posittion_x(int new_x) { x = new_x; }
	void Set_new_posittion_y(int new_y) { y = new_y; }
};

