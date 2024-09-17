#include<iostream>
#include "weapon.h"

weapon::weapon(float g_damage, float g_weight, float g_block, float g_missing)
	:damage(Set_damage(g_damage)), weight(Set_weight(g_weight)), block(Set_block(g_block)), missing(Set_missing(g_missing))
{}
