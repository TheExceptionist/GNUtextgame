#ifndef STATUS_H
#define STATUS_H

#include "util.h"

void initStatusEffects();
void deleteStatusEffects();

struct StatusEffect
{
	StatusEffect(const std::string name, const int rate, const int recover_chance,
		const int health, const int speed, const int agility, const int skill,
		const int p_str, const int e_str, const int s_str,
		const int p_dur, const int e_dur, const int s_dur)
	: m_name(name),
	  m_recover_chance(recover_chance),
	  m_rate(rate)
	{
		static int ID = 0;
		m_id = ID++;

		m_effected_stats[HEALTH] = health;
		m_effected_stats[SPEED] = speed;
		m_effected_stats[AGILITY] = agility;
		m_effected_stats[SKILL] = skill;

		m_effected_stats[P_STR] = p_str;
		m_effected_stats[E_STR] = e_str;
		m_effected_stats[S_STR] = s_str;

		m_effected_stats[P_DUR] = p_dur;
		m_effected_stats[E_DUR] = e_dur;
		m_effected_stats[S_DUR] = s_dur;
	}

	const std::string m_name;
	const int m_rate;
	const int m_recover_chance;
	int m_effected_stats[NUM_STATS];
	int m_id;
};

extern const StatusEffect* g_effects[NUM_STATUS_EFFECTS];

#endif