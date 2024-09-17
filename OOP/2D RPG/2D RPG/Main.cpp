#include<iostream>
#include"Unit/Unit.h"

int main()
{
	weapon Sword(3.4, 11, 15, 23.44);
	weapon Bow(0, -3, 11, -23.4);
	
	Sword.Show_W();
	std::cout<<std::endl;
	Bow.Show_W();
	return 0;
}