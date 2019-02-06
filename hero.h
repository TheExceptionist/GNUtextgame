#ifndef HERO_H
#define HERO_H

#include "power.h"
#include "entity_data.h"
#include "filesystem.h"

static const int CRIT_BONUS = 3;
static const int LEVEL_REQ = 5;
static const int BASIC_LEVEL_POINTS = 2;
static const int OFFENSIVE_LEVEL_POINTS = 1;
static const int DEFENSIVE_LEVEL_POINTS = 1;
static const int ATTACKS_PER_SPEED = 5;
static const int START_LEVEL_POINTS = 45;

class Hero 
{
public:
	Hero() {}
	Hero(const std::string name, const int is_organic = 0);
	~Hero();

	void init(const int is_organic = 0);
	void levelUp();
	void printStatLine(const int stat);

	void setStat(const int slot, const int amount) { m_stats[slot] = amount; }
	void addStat(const int slot, const int amount) { m_stats[slot] += amount; }
	void addStatTotal(const int slot, const int amount) { m_total_stats[slot] += amount; }
	void set(const int health, const int speed, const int agility, const int skill, const int p_str, const int e_str, const int s_str, const int p_dur, const int e_dur, const int s_dur);
	void add(const int health, const int speed, const int agility, const int skill, const int p_str, const int e_str, const int s_str, const int p_dur, const int e_dur, const int s_dur);
	int getStat(const int slot) const { return m_stats[slot]; }
	
	void setChances(const int health, const int speed, const int agility, const int skill, const int p_str, const int e_str, const int s_str, const int p_dur, const int e_dur, const int s_dur);
	void setChancesSlot(const int slot, const int amount) { m_stat_chances[slot] = amount; }//const int health, const int speed, const int agility, const int skill, const int p_str, const int e_str, const int s_str, const int p_dur, const int e_dur, const int s_dur);
	int getChance(const int slot) { return m_stat_chances[slot]; }

	void clearBonusStats() { for(int i = 0; i < NUM_STATS; i++) m_bonus_stats[i] = 0; }
	void updateBonusStats();
	void updateStatTotal();
	void updateStats();
	int getEffectiveDamageOutput(const int attack_type);
	int getEffectiveDamageReduction(const int attack_type);

	void backup();
	void reset();

	Power* getPower(const int slot) { return m_powers.at(slot); }
	bool hasPower(Power* p) 
	{ 
		for(auto iter = m_powers.begin(); iter != m_powers.end(); ++iter) 
		{
			Power* pow = *iter;
			
			if(pow == p)
			{
				return true;
			}
		} 

		return false;
	}

	int getNumPowers() { return m_powers.size(); }
	std::vector<Power *>& getPowers() { return m_powers; }
	void addPower(Power* power, const bool update = true);

	Attribute* getAttribute(const int slot) { return m_attr.at(slot); }
	void addAttribute(Attribute* attr) { m_attr.push_back(attr); }
	void removeAttribute(const int slot) { if(m_attr.size() > slot) m_attr.erase(m_attr.begin() + slot); }

	bool canHealFromDamage() { return m_can_heal_from_damage; }
	void setCanHeal(const bool heal) { m_can_heal_from_damage = heal; }

	void updateMoveset();

	void setLevel(const int num) { m_level = num; }
	int getLevel() { return m_level; }

	void addMove(const Move& move, const bool display = false);
	void removeMove(const int slot);
	void updateMoveSlots(const int curr_slots);
	Move* getMove(const int slot) { if(slot < m_num_moves) return m_moves[slot]; else return NULL;}
	int getNumMoves() { return m_num_moves; }
	Move* getRandomMove(const bool attack = true);
	void moveReplacePrompt(const Move& move);
	void printStats();
	void printDescription();

	int getStatTotal(const int slot) { return m_total_stats[slot]; }
	int getStatBonus(const int slot) { return m_bonus_stats[slot]; }

	double getChanceToHit(Hero& defender, Move* move);
	int getChanceToCrit(Hero& defender, Move* move);

	std::string doMove(Hero& attacker, Move* move, const bool debug = false);
	std::string doHeal(Hero& healer, Move* move, const bool debug = false);

	void addEffect(const StatusEffect *effect) { m_effects.push_back(effect); }
	void removeEffect(const int index) { if(index < m_effects.size()) m_effects.erase(m_effects.begin() + index); }
	const StatusEffect* getEffect(const int index) { if(index < m_effects.size()) return m_effects.at(index); else return NULL; }
	int getNumEffects() { return m_effects.size(); }
	bool isAfflicted() { return !m_effects.empty(); }
	void applyEffect(const StatusEffect *effect);

	int getEffectiveDefenseStat(const int damage_type);
	int getEffectiveOffensiveStat(const int damage_type);

	void applyDamage(const int amount) { m_total_stats[HEALTH] -= amount; }
	Move* selectMovePrompt();

	void setNewReq() { m_level_req *= 2; }
	void setLevelReq(const int amount) { m_level_req = amount; }
	int getLevelReq() { return m_level_req; }
	int getTotalMoveProficiency() 
	{ 
		int total_proficiency = 0;
		for(int i = 0; i < m_num_moves; i++)
			total_proficiency += m_moves[i]->getProficiency();

		return total_proficiency;
	}
	void checkProficiency()
	{
		if(getTotalMoveProficiency() > getLevelReq()) levelUp();
	}

	void setEyeColor(const int color) { m_eye_id = color;}
	void setHairColor(const int color) { m_hair_id = color;}
	void setOrigin(const int origin) { m_origin_id = origin;}
	void setMartialStatus(const int status) { m_martial_status = status;}

	int getEyeColorID() { return m_eye_id;}
	int getHairColorID() { return m_hair_id;}
	int getOriginID() { return m_origin_id;}
	int getMartialStatusID() { return m_martial_status;}

	std::string getEyeColor() { return eye_colors[m_eye_id]; }
	std::string getHairColor() { return hair_colors[m_hair_id]; }
	std::string getOrigin() { return origins[m_origin_id]; }
	std::string getMartialStatus() { return martial_statuses[m_martial_status]; }
	std::string getGenderSymbol() { return m_is_female ? "F" : "M";}

	int getFeet() { return m_feet; }
	int getInches() { return m_inches; }
	int getWeight() { return m_weight; }
	void setFeet(const int num) { m_feet = num; }
	void setInches(const int num) { m_inches = num; }
	void setWeight(const int num) { m_weight = num; }

	std::string getGenderString() { return m_is_female ? "Female" : "Male"; }
	bool getGender() { return m_is_female; }
	void setGender(const bool female) { m_is_female = female; }

	std::string getName() { return m_name; }
	std::string getNickname() { return m_nickname; }

	void setDay(const int day) { m_day = day;}
	void setBirthplace(const std::string name) { m_birth_place = name; } 
	void setDescription(const std::string str) { m_description_str = str;}

	void setName(const std::string name) { m_name = name; }
	void setNickname(const std::string nickname) { m_nickname = nickname; }
	void setAge(const int age) { m_age = age; }
	void setYear(const int year) { m_year = year; }
	void setMonth(const std::string month_str);
	void setOrganic(const int is_organic) { m_is_organic = is_organic; }
	int getOrganic() { return m_is_organic; }
	int getAge() { return m_age; }
	int getYear() { return m_year; }
	int getMonth() { return m_month; }
	int getDay() { return m_day; }

	std::string getMonthStr() { return m_month_str; }
	std::string getBirthplace() { return m_birth_place; }
	std::string getDescription() { return m_description_str; }

	void readSaveData(const std::string filename, const int dir, const bool debug = false);
	void saveData(const std::string filename, const int dir);
	void savePrompt();
	void readPrompt(const bool debug = false);

	void printMoves(const bool combat = false);
	void randomizeStats(const bool super = false);
	void fillOutCharacter();
private:
	std::string m_name;
	std::string m_nickname;

	int m_stats[NUM_STATS] = {};
	int m_bonus_stats[NUM_STATS] = {};
	int m_total_stats[NUM_STATS] = {};
	int m_stat_chances[NUM_STATS] = {};
	int m_level;
	int m_level_req = LEVEL_REQ;
	bool m_can_heal_from_damage = false;
	int m_is_organic;

	std::vector<Attribute *> m_attr;
	std::vector<Power *> m_powers;
	std::vector<const StatusEffect *> m_effects;

	Move* m_moves[MAX_MOVES] = {};
	int m_num_moves = 0;

	bool m_is_female = false;
	int m_eye_id = 0;
	int m_hair_id = 0;
	int m_origin_id = 0;
	int m_martial_status = 0;
	int m_feet = 4;
	int m_inches = 1;
	int m_weight = 40;
	int m_age = 0;
	int m_year = 0;
	int m_month = 0;
	int m_day = 0;

	std::string m_month_str;
	std::string m_birth_place;
	std::string m_description_str;

	int getHitChanceBonus();
	int getDodgeChanceBonus();
	int getCritChanceBonus();
	void clearMoves();
};

void listEyeColors();
void listHairColors();
void listOrigins();
void listMartialStatuses();
std::string getRandomName(const bool is_female);


#endif