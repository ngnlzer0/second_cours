#pragma once
#include<iostream>
class weapon
{
private:
	float damage;
	float weight;
	float block;
	float missing;
public:
    weapon(float g_damage = 0.0, float g_weight = 0.0, float g_block = 0.0, float g_missing = 0.0);

	float Get_damage() { return damage; }
	float Get_weight() { return weight; }
	float Get_block() { return block; }
	float Get_missing() { return missing; }

	float Set_damage(float g_damage)  { return(g_damage > 0.0 ? damage = g_damage : damage = 0.0); }
	float Set_weight(float g_weight)  { return(g_weight > 0.0 ? weight = g_weight : weight = 0.0); }
	float Set_block(float g_block)    { return (g_block > 0.0 ? block = g_block : block = 0.0); }
	float Set_missing(float g_missing){ return (g_missing > 0.0 ? missing = g_missing : missing = 0.0); }

	void Show_W()
	{
		std::cout << "D = " << damage << ", W = " << weight << ", B = " << block << ", M = " << missing;
	}
};

