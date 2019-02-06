#include "power.h"
#include "console.h"

Power* powers[NUM_POWERS];

void initPower()
{
	powers[SUPER_STRENGTH] = new Power("Super Strength", SUPER_STRENGTH);
	powers[SUPER_STRENGTH]->addMove(g_moves[PUNCH]);
	powers[SUPER_STRENGTH]->addMove(g_moves[KICK]);
	powers[SUPER_STRENGTH]->addMove(g_moves[POWER_PUNCH]);
	powers[SUPER_STRENGTH]->addMove(g_moves[THROW_ROCK]);
	powers[SUPER_STRENGTH]->addMove(g_moves[CHARGE]);
	powers[SUPER_STRENGTH]->addMove(g_moves[BLOCK]);
	powers[SUPER_STRENGTH]->addMove(g_moves[TENSE]);

	powers[SUPER_STRENGTH]->addAttribute(g_attributes[ENHANCED_STRENGTH]);

	powers[SSRD_RIFLE_1] = new Power("SSRD R14 M1", SSRD_RIFLE_1);
	powers[SSRD_RIFLE_1]->addMove(g_moves[BOLT_ACTION_SHOT]);
	powers[SSRD_RIFLE_1]->addMove(g_moves[TAKE_AIM]);
	powers[SSRD_RIFLE_1]->addMove(g_moves[SEMI_AUTO_SHOT]);
	powers[SSRD_RIFLE_1]->addMove(g_moves[VOLLEY_SHOT]);
	powers[SSRD_RIFLE_1]->addMove(g_moves[FULL_AUTO_SHOT]);
}

Power* getRandomPower(const bool super)
{
	using namespace e_std;

	if(super) return powers[randInt(0, SSRD_RIFLE_1)];
	else return powers[randInt(0, NUM_POWERS)];
}

void listPowers()
{
	for(int i = 0; i < NUM_POWERS; i++)
	{
		e_std::println(std::to_string(i)+": "+powers[i]->m_name);
	}
}

void deletePower()
{
	for(int i = 0; i < NUM_POWERS; i++)
	{
		delete powers[i];
	}
}