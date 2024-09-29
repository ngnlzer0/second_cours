#pragma once

const int HIGHT = 20;
const int WIDTH = 30;

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

