#pragma once
#include"Unit.h"
#include"Unit_sprite/Unit_Sprite.h"


class Hero : public Unit
{
private:
	static std::map<std::string, Animation> hero_animations;

	Unit_Sprite hero_sprite;

public:
	Hero();

	Unit_Sprite* Get_sprite() { return &hero_sprite; };
};

