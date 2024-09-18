#include"Unit/Unit.h"

int main()
{
	weapon Sword1(Bow, 3.4, 11.0, 15.0, 23.44,11);
	weapon Bow(Staff, -3.0, 11.0, -23.4,12.0,50);
	
	Show_weapon(Sword1);
	std::cout<<std::endl;
	Show_weapon(Bow);
	Bow.Get_type_weapone();

	return 0;
}