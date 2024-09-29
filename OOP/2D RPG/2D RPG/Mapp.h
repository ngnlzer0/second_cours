#pragma once

const int HIGHT = 45;
const int WIDTH = 60;

enum object_in
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
	object_in Maps[HIGHT][WIDTH];

};

