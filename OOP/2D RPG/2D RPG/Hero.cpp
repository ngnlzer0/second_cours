#include "Hero.h"


std::map<std::string, Animation> hero_animations = {
	{"attack",Animation {"C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_Attack.png",
	 4,{0,0,120,80}}},
	{"runing",Animation {"C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Colour1/NoOutline/120x80_PNGSheets/_Dash.png",
	 2, {0,0,120,80}}},
	{"attack_combo",Animation{"C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Colour1/Outline/120x80_PNGSheets/_AttackCombo2hit.png",
	 10,{0,0,120,80}}},
	{"idle", Animation{"C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Comparison2x.png",
	 1,{0,0,120,80}}}
};

Hero::Hero()
	:hero_sprite("C:/Git.repos/second_cours/OOP/2D RPG/2D RPG/assets/FreeKnight_v1/Comparison2x.png",{0,0},true,{0,0,120,80})
{

}
