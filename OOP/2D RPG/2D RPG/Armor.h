#pragma once

enum Armor_type
{
	helmet,
	jacket,
	gloves,
	pants,
	shoes,
};

class Armor
{
private:
	Armor_type type;
	double weight;
	double block;
	double miss;
	int durability;

public:
	Armor(double g_weight = 0.0, double  g_block = 0.0, double  g_missing = 0.0, int g_durability = 0, Armor_type g_type = helmet, bool random = 1);
	Armor* operator* () { return this; }

	double  Get_weight() { return weight; }
	double  Get_block() { return block; }
	double  Get_missing() { return miss; }
	int Get_durability() { return durability; }

	double  Set_weight(double  g_weight) { return(g_weight > 0.0 ? weight = g_weight : weight = 0.0); }
	double  Set_block(double  g_block) { return (block = g_block); }
	double  Set_missing(double  g_missing) { return (miss = g_missing); }
	int Set_durability(int g_durability) { return (g_durability > 0 ? durability = g_durability : durability = 0); }

};

