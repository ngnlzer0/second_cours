#pragma once
#include "Armor/Armor.h"
int const num_weapon_type = 4;
enum weapon_type
{
	Sword = 0,
	Bow = 1,
	Sword_and_shield = 2,
	Staff = 3 
};

class Gloves :virtual public Armor
{
private:
	double attack_speed;
	bool available_weapons[num_weapon_type];
	int chance_add_attack;
public:
	Gloves(double  g_weight = 0.0, double  g_block = 0.0, double  g_missing = 0.0, int g_durability = 0,double g_attack_speed = 0, int chance_add_attack = 0, bool type[num_weapon_type]);

	double Get_attack_speed() { return attack_speed; }
	bool check_avaliable_weapon(int i) { return available_weapons[i]; }
	int Get_chance_add_attack() { return chance_add_attack; }

	void Set_attack_speed(double g_attack_speed) { attack_speed = g_attack_speed; }
	void Set_avaliable_weapon(bool having, int type) { available_weapons[type] = having; }
	void Set_chance_add_attack(int g_chance_add_attack) { chance_add_attack = g_chance_add_attack; }
};

