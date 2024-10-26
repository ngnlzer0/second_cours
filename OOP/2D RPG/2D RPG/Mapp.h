#pragma once

const int WIDHT_Mapp = 1920;
const int HIGHT_Mapp = 1040;
const int NUMBER_TIEL_IN_WIDTH = WIDHT_Mapp / 16;
const int NUMBER_TIEL_IN_HIGHT = HIGHT_Mapp / 16;

enum tiels
{
	ground = 1,
	wall = 2,
	door = 3,
	unit = 11,
	hero = 12,
	chest = 21,
};


class Mapp
{
protected:
	tiels Mapptiels[NUMBER_TIEL_IN_HIGHT][NUMBER_TIEL_IN_WIDTH];
public:
	Mapp();
};

