#include "Hero.h"

Hero::Hero(const double max_weight ,const double g_max_hp, const int g_max_stamina, int g_speed, double g_block, double g_miss, int g_money )
	:Unit(max_weight,g_max_hp, g_max_stamina,  g_speed,  g_block, g_miss),money(g_money)
{
}
