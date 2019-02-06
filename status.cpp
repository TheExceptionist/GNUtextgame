#include "status.h"

const StatusEffect* g_effects[NUM_STATUS_EFFECTS];

void deleteStatusEffects()
{
	for(int i = 0; i < NUM_STATUS_EFFECTS; i++)
	{
		delete g_effects[i];
	}
}

void initStatusEffects()
{
	g_effects[STUN] = new StatusEffect("Stun", 1, 20, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0);
	g_effects[BLEED] = new StatusEffect("Bleed", 1, 40, -2, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	g_effects[AFFLICT] = new StatusEffect("Afflict", 2, 15, -1, 0, 0, 0, 0, 0, 0, -1, -1, 0);
	g_effects[FIRE] = new StatusEffect("Fire", 1, 50, -1, 1, 1, 0, -2, 0, 0, -2, 0, 0);
	g_effects[DISORIENT] = new StatusEffect("Disorient", 2, 30, 0, 0, 0, 0, 0, 0, -3, 0, 0, -3);
	g_effects[FREEZE] = new StatusEffect("Freeze", 2, 35, 0, -2, -2, -2, 0, -1, 0, 1, 0, 0);
	g_effects[CURSE] = new StatusEffect("Curse", 3, 10, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1);
}
