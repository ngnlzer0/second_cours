#pragma once
#include"weapon.h"
#include"Armor.h"
#include"Inventors.h"
#include"position.h"

class Unit : virtual public position
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

	Unit(int X = 0, int Y = 0, const double max_weight = 50, const double g_max_hp = 150, const int g_max_stamina = 100,
		int g_speed = 50, double g_block = 40, double g_miss = 25);
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
	void push_stamina_self();

	weapon* Get_weapon() { return c_weapon; }
	Armor* Get_armor() { return c_armor; }

	void Set_new_weapon(weapon* new_weapon) { c_weapon = new_weapon; }
	void Set_new_armor(Armor* new_armor) { c_armor = new_armor; }

	bool aliwe() { if (this->Get_HP() <= 0) { delete this; return false; } return true; }

	void Get_accet_monstr(Unit* other);
	void user_step(Unit* other);
	void Show_info();
};

void Fight(Unit* hero, Unit* monstr);

