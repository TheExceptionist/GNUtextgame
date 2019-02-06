#include "attack_type.h"

AttackType* g_attack_types[NUM_ATTACK_TYPES];

void deleteAttackTypes()
{
	for(int i = 0; i < NUM_ATTACK_TYPES; i++)
	{
		delete g_attack_types[i];
	}
}


void initAttackTypes()
{
	g_attack_types[BLUNT] = new AttackType("Blunt", BLUNT, g_effects[STUN]);
	g_attack_types[CUTTING] = new AttackType("Cutting", CUTTING, g_effects[BLEED]);
	g_attack_types[PIERCING] = new AttackType("Piercing", PIERCING, g_effects[BLEED]);
	g_attack_types[POISON] = new AttackType("Poison", POISON, g_effects[POISON]);
	g_attack_types[LIGHT] = new AttackType("Light", LIGHT, g_effects[FIRE]);
	g_attack_types[HEAT] = new AttackType("Heat", HEAT, g_effects[FIRE]);
	g_attack_types[COLD] = new AttackType("Cold", COLD, g_effects[FREEZE]);
	g_attack_types[ELECTRIC] = new AttackType("Electric", ELECTRIC, g_effects[STUN]);
	g_attack_types[WAVE] = new AttackType("Wave", WAVE, g_effects[DISORIENT]);
	g_attack_types[PLASMA] = new AttackType("Plasma", PLASMA, g_effects[FIRE]);
	g_attack_types[MIND] = new AttackType("Mind", MIND, g_effects[DISORIENT]);
	g_attack_types[TIME] = new AttackType("Time", TIME, g_effects[FREEZE]);
	g_attack_types[SPACE] = new AttackType("Space", SPACE, g_effects[DISORIENT]);
	g_attack_types[BLOOD] = new AttackType("Blood", BLOOD, g_effects[AFFLICT]);
	g_attack_types[DEATH] = new AttackType("Death", DEATH, g_effects[CURSE]);
	g_attack_types[ACID] = new AttackType("Acid", ACID, g_effects[AFFLICT]);
	g_attack_types[COMBUSTION] = new AttackType("Combustion", COMBUSTION, g_effects[DISORIENT]);

}
