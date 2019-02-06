#include "move.h"
#include "console.h"

Move* g_moves[NUM_MOVES];

Move::Move(const std::string name, const int ID, const int damage_type, const bool is_attack, const int level, const int base_cooldown, 
	const float hit, const float alignment_chance, const int uses_lim, const float times, const float crit_bonus,
	const float piercing, const float ignore)
: m_name(name),
  m_id(ID),
  m_is_attack(is_attack),
  m_level(level),
  m_damage_type(damage_type),
  m_base_cooldown(base_cooldown),
  m_hit(hit),
  m_crit(crit_bonus),
  m_piercing(piercing),
  m_times(times),
  m_ignore(ignore),
  m_alignment_chance(alignment_chance),
  m_uses_lim(uses_lim)
{

}

Move::Move(const Move& move)
: m_name(move.getName()),
  m_id(move.getID()),
  m_is_attack(move.isAttack()),
  m_level(move.getLevelReq()),
  m_damage_type(move.getDamageType()),
  m_base_cooldown(move.getBaseCooldown()),
  m_hit(move.getHit()),
  m_crit(move.getCrit()),
  m_times(move.getTimes()),
  m_piercing(move.getPiercing()),
  m_ignore(move.getIgnore()),
  m_alignment_chance(move.getAlignmentChance()),
  m_uses_lim(move.getLim())
{
	for(int i = 0; i < NUM_STATS; i++)
	{
		m_stats_effected[i] = move.getStat(i);
	}

	m_attack_types = move.getTypes();
	m_extra_effects = move.getEffects();
}

void Move::printStats()
{
	e_std::print(getName() + " [Uses: " + std::to_string(m_uses) + " To next proficiency: " + std::to_string(m_uses_lim) + " Proficiency: " + std::to_string(m_proficiency) + "]");
}

void Move::printCombatStats()
{
	e_std::print(getName() + " [Dam: " + getDamageTypeString(getDamageType()) + " Hit: "+ std::to_string((int)m_hit) + " Crit: " + std::to_string((int)m_crit) + " Pierce: " + std::to_string((int)m_piercing) + " Ignore: " + std::to_string((int)m_ignore) + " Times: x" + std::to_string((int)m_times)+ "]");
}

bool Move::shouldGiveEffect()
{
	using namespace e_std;

	return randInt(0, 100) < m_alignment_chance; 
}

void Move::upgrade()
{
	m_proficiency++;
	m_uses = 0;

	m_hit += m_hit * proficiency_bonus;
	m_crit += m_crit * proficiency_bonus;
	m_piercing += m_piercing * proficiency_bonus;
	m_ignore += m_ignore * proficiency_bonus;
	m_times += m_times * proficiency_bonus;
	m_alignment_chance += m_times * proficiency_bonus;

	for(int i = 0; i < NUM_STATS; i++)
	{
		m_stats_effected[NUM_STATS] += m_stats_effected[NUM_STATS] * proficiency_bonus;
	}

	setNewLim();
}

const StatusEffect* Move::getRandomEffect()
{
	using namespace e_std;
	std::vector<const StatusEffect *> all_effects;

	for(auto p = m_attack_types.begin(); p != m_attack_types.end(); ++p)
	{
		AttackType *type = *p;

		all_effects.push_back(type->m_effect);
	}

	for(auto e  = m_extra_effects.begin(); e != m_extra_effects.end(); ++e)
	{
		all_effects.push_back(*e);
	}

	return all_effects.at(randInt(0, all_effects.size()));
}

void initMove()
{
	g_moves[PUNCH] = new Move("Punch", PUNCH, true, 1, 0, 0, 0, 5);
	g_moves[PUNCH]->set(-1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	g_moves[PUNCH]->addType(g_attack_types[BLUNT]);

	g_moves[KICK] = new Move("Kick", KICK, true, 1, 0, -5, 0, 5, 1, 0, 1, 0);
	g_moves[KICK]->set(-1, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	g_moves[KICK]->addType(g_attack_types[BLUNT]);

	g_moves[POWER_PUNCH] = new Move("Power Punch", POWER_PUNCH, true, 1, 0, -10, 0, 10, 1, 0, 0, 0.05);
	g_moves[POWER_PUNCH]->set(-3, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	g_moves[POWER_PUNCH]->addType(g_attack_types[BLUNT]);
	g_moves[POWER_PUNCH]->addType(g_attack_types[PIERCING]);

	g_moves[THROW_ROCK] = new Move("Throw Rock", THROW_ROCK, true, 3, 0, 0, 0, 5);
	g_moves[THROW_ROCK]->set(-5, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	g_moves[THROW_ROCK]->addType(g_attack_types[PIERCING]);

	g_moves[CHARGE] = new Move("Charge", CHARGE, true, 5, 0, -5, 0, 5, 1, 0, 3, 0);
	g_moves[CHARGE]->set(-3, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	g_moves[CHARGE]->addType(g_attack_types[BLUNT]);

	g_moves[BLOCK] = new Move("Block", BLOCK, false, 7, 1, 80, 0, 5);
	g_moves[BLOCK]->set(0, 0, 0, 0, 0, 0, 0, 3, 0, 0);
	g_moves[BLOCK]->addType(g_attack_types[BLUNT]);

	g_moves[TENSE] = new Move("Tense Up", TENSE, false, 10, 3, 100, 0, 5);
	g_moves[TENSE]->set(0, 0, 0, 0, 3, 0, 0, 0, 0, 0);
	g_moves[TENSE]->addType(g_attack_types[BLUNT]);

	g_moves[BOLT_ACTION_SHOT] = new Move("Bolt Action Shot", BOLT_ACTION_SHOT, true, 1, 0, 0, 0, 5, 1, 0, 5, 0);
	g_moves[BOLT_ACTION_SHOT]->addType(g_attack_types[PIERCING]);

	g_moves[TAKE_AIM] = new Move("Take Aim", TAKE_AIM, false, 1, 5, 100, 0, 10);//, 5, 1, 0, 5, 0);
	g_moves[TAKE_AIM]->set(0, 0, 3, 3, 0, 0, 0, 0, 0, 0);
	g_moves[TAKE_AIM]->addType(g_attack_types[BLUNT]);

	g_moves[SEMI_AUTO_SHOT] = new Move("Semi Auto Shot", SEMI_AUTO_SHOT, true, 3, 0, 0, 0, 5, 2, 0, 3, 0);
	g_moves[SEMI_AUTO_SHOT]->addType(g_attack_types[PIERCING]);

	g_moves[VOLLEY_SHOT] = new Move("Volley Shot", VOLLEY_SHOT, true, 5, 0, 0, 0, 5, 3, 0, 2, 0);
	g_moves[VOLLEY_SHOT]->addType(g_attack_types[PIERCING]);

	g_moves[FULL_AUTO_SHOT] = new Move("Full Auto Shot", FULL_AUTO_SHOT, true, 10, 0, 0, 0, 5, 5, 0, 1, 0);
	g_moves[FULL_AUTO_SHOT]->addType(g_attack_types[PIERCING]);
}

void deleteMove()
{
	for(int i = 0; i < NUM_MOVES; i++)
	{
		delete g_moves[i];
	}
}