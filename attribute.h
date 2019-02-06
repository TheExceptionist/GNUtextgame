#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "defs.h"

void initAttributes();
void deleteAttributes();

struct Attribute
{
	Attribute(const std::string name, const int dodge_chance, const int hit_chance, const int crit_chance)
	: m_name(name),
	  m_dodge_chance(dodge_chance),
	  m_hit_chance(hit_chance),
	  m_crit_chance(crit_chance)
	{
		reset();
	}

	void set(const int health, const int speed, const int agility, const int skill, const int p_str, const int e_str, const int s_str, const int p_dur, const int e_dur, const int s_dur)
	{
		m_stat_bonus[HEALTH] = health;
		m_stat_bonus[SPEED] = speed;
		m_stat_bonus[AGILITY] = agility;
		m_stat_bonus[SKILL] = skill;

		m_stat_bonus[P_STR] = p_str;
		m_stat_bonus[E_STR] = e_str;
		m_stat_bonus[S_STR] = s_str;

		m_stat_bonus[P_DUR] = p_dur;
		m_stat_bonus[E_DUR] = e_dur;
		m_stat_bonus[S_DUR] = s_dur;
	}

	void reset()
	{
		for(int i = 0; i < NUM_ATTACK_TYPES; i++)
		{
			m_attack_type_bonus[i] = 0;
		}

		for(int i = 0; i < NUM_ATTACK_TYPES; i++)
		{
			m_attack_type_reduction[i] = 0;
		}
	}

	const std::string m_name;
	const int m_dodge_chance;
	const int m_hit_chance;
	const int m_crit_chance;
	const bool m_heal_from_damage = false;
	int m_stat_bonus[NUM_STATS];
	int m_attack_type_bonus[NUM_ATTACK_TYPES];
	int m_attack_type_reduction[NUM_ATTACK_TYPES];
};

extern Attribute* g_attributes[NUM_ATTRIBUTES];

#endif