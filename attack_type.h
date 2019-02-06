#ifndef ATTACKTYPE_H
#define ATTACKTYPE_H

#include "status.h"

void initAttackTypes();
void deleteAttackTypes();

struct AttackType
{
	AttackType(const std::string name, const int ID, const StatusEffect* effect = NULL)
	: m_name(name),
	  m_effect(effect),
	  m_id(ID)
	{
		
	}

	const std::string m_name;
	const StatusEffect* m_effect;
	const int m_id;
};

extern AttackType* g_attack_types[NUM_ATTACK_TYPES];

#endif