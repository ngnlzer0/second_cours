#pragma once
#include <unordered_map>
#include<iostream>
#include"Buttons.h"
#include "BaseItem.h"

enum weapon_type
{
	Sword = 0,
	Bow = 1,
	Sword_and_shield = 2,
	Staff = 3
};

class weapon : public BaseItem
{
private:
	Buttons* weapon_button;
	weapon_type type;
	double  damage;
	double  weight;
	double  block;
	double  missing;
	int durability;

	static const std::unordered_map<weapon_type, std::string> weaponTexturePaths;

public:
    weapon(int pos_x = 0, int pos_y = 0, double g_damage = 0.0, double  g_weight = 0.0, double  g_block = 0.0, double  g_missing = 0.0,
		int g_durability = 0, weapon_type g_Type = Sword, bool random = 1);
	weapon* operator* () { return this; }

	double  Get_damage() { return damage; }
	double  Get_weight() { return weight; }
	double  Get_block() { return block; }
	double  Get_missing() { return missing; }
	int Get_durability() { return durability; }

	double  Set_damage(double  g_damage)  { return(g_damage > 0.0 ? damage = g_damage : damage = 0.0); }
	double  Set_weight(double  g_weight)  { return(g_weight > 0.0 ? weight = g_weight : weight = 0.0); }
	double  Set_block(double  g_block)    { return (g_block > 0.0 ? block = g_block : block = 0.0); }
	double  Set_missing(double  g_missing){ return (g_missing > 0.0 ? missing = g_missing : missing = 0.0); }
	int Set_durability(int g_durability) { return (g_durability > 0 ? durability = g_durability : durability = 0); }
	weapon_type Get_type_weapon() { std::cout << "you weapon is " << type; return type; }


	Buttons& Get_Buttons() { return *weapon_button; }
};

