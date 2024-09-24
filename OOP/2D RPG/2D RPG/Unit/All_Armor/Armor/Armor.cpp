#include "Armor.h"

Armor::Armor(double g_weight, double g_block, double g_missing, int g_durability)
	: weight(Set_weight(g_weight)), block(Set_block(g_block)),miss(Set_missing(g_missing)),durability(Set_durability(g_durability))
{
}
