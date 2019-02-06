#ifndef MOVE_H
#define MOVE_H

#include "defs.h"
#include "attack_type.h"
#include "emitter.h"

enum 
{
	SELF_ONLY,
	OTHERS_ONLY,
	SELF_AND_OTHERS
};

const double proficiency_bonus = 0.05;

void initMove();
void deleteMove();

class Move : public Emitter
{
public:
	Move(const std::string name, const int ID, const int damage_type, const bool is_attack, const int level, const int base_cooldown, 
		const float hit, const float alignment_chance, const int uses_lim, const float times = 1, 
		const float crit_bonus = 0, const float piercing = 0, const float ignore = 0);
	Move(const Move& move);

	~Move(){}


	void decrementCooldown() { if(m_cooldown > 0) m_cooldown--; }
	void startCooldown() { m_cooldown = m_base_cooldown; }
	bool needsCooldown() { if(m_cooldown <= 0) return false; else return true;}

	bool shouldGiveEffect();
	const StatusEffect* getRandomEffect();

	void addType(AttackType *type) { m_attack_types.push_back(type); }
	void addEffect(const StatusEffect * const effect) { m_extra_effects.push_back(effect); }

	void increaseProficiency() { m_proficiency++; }
	void setNewLim() { m_uses_lim *= 2; }
	void upgrade();
	void increaseUses() 
	{ 
		if(m_uses_lim >= m_uses) m_uses++; 
		else 
		{
			upgrade();
		}
	}
	void use()
	{
		startCooldown();
		increaseUses();
	}

	void set(const int health, const int speed, const int agility, const int skill, const int p_str, const int e_str, const int s_str, const int p_dur, const int e_dur, const int s_dur)
	{
		m_stats_effected[HEALTH] = health;
		m_stats_effected[SPEED] = speed;
		m_stats_effected[AGILITY] = agility;
		m_stats_effected[SKILL] = skill;

		m_stats_effected[P_STR] = p_str;
		m_stats_effected[E_STR] = e_str;
		m_stats_effected[S_STR] = s_str;

		m_stats_effected[P_DUR] = p_dur;
		m_stats_effected[E_DUR] = e_dur;
		m_stats_effected[S_DUR] = s_dur;
	}

	int getStat(const int slot) const { return (int)m_stats_effected[slot]; }
	int getLevelReq() const { return m_level; }
	std::string getName() const { return m_name; }

	int getHitChance() const { return (int)m_hit; }
	int getPiercing() const { return (int)m_piercing; }
	float getIgnore() const { return m_ignore; }
	int getTimes() const { return (int)m_times; }
	int getAlignmentChance() const {  return(int) m_alignment_chance; }
	int getProficiency() const { return m_proficiency; }
	int getHit() const { return m_hit; }
	int getCrit() const { return m_crit; }
	int getLim() const { return m_uses_lim; }
	int getUses() const { return m_uses; }
	int getBaseCooldown() const { return m_base_cooldown; }
	int getCooldown() const { return m_cooldown; }
	bool isAttack() const {  return m_is_attack; }
	const std::vector<AttackType *>& getTypes() const { return m_attack_types; }
	const std::vector<const StatusEffect *>& getEffects() const { return m_extra_effects; }

	void printStats();
	void printCombatStats();

	void setProficiency(const int amount) { m_proficiency = amount; }
	void setLim(const int amount) { m_uses_lim = amount; }
	void setUses(const int amount) { m_uses = amount; }
	int getID() const { return m_id; }

	int getEffected() { return m_type; }
	void setEffected(const int type) { m_type = type; } 

	int getDamageType() { return m_damage_type; }
protected:
	const std::string m_name;
	const int m_base_cooldown;
	const int m_level;
	const int m_damage_type;
	const bool m_is_attack;
	float m_alignment_chance;
	float m_hit;
	float m_crit;
	float m_piercing;
	float m_ignore;
	float m_times;
	int m_type = SELF_ONLY;
	int m_cooldown;
	int m_proficiency = 1;
	int m_uses = 0;
	int m_uses_lim;
	int m_id;

	float m_stats_effected[NUM_STATS];

	std::vector<AttackType *> m_attack_types;
	std::vector<const StatusEffect *> m_extra_effects;
};

extern Move* g_moves[NUM_MOVES];

#endif 