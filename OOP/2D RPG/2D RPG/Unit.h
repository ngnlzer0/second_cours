#pragma once
#include"weapon.h"
#include"Armor.h"
#include"Inventors.h"

class Unit
{
private:
	weapon* c_weapon;
	Armor* c_armor;

	const double max_HP;
	const int max_stamina;
	double HP;
	int stamina;
	int speed;
	double block;
	double miss;

	const double max_weight;
	double cur_weight;
public:

	Inventors inventar;

	Unit(const double max_weight = 50, const double g_max_hp = 150, const int g_max_stamina = 100, int g_speed = 50, double g_block = 40, double g_miss = 25);
	~Unit() = default;

	const double Get_max_HP() { return max_HP; }
	const int Get_max_stamina() { return max_stamina; }
	double Get_HP() { return HP; }
	int Get_stamina() { return stamina; }
	int Get_speed() { return speed; }
	double Get_block() { return block; }
	double Get_miss() { return miss; }

	void Set_new_HP(double new_HP) { new_HP < max_HP ? HP = new_HP : HP = max_HP; }
	void Set_new_stamina(int new_stamina) { new_stamina < max_stamina ? stamina = new_stamina : stamina = max_stamina; }
	
	void received_damage(double minus_damage);
	void attack_enemi(Unit* enemi);

	void Healt_self();

	void Swap_weapon(weapon* other);
};

