#include "hero.h"
#include "console.h"

Hero::Hero(const std::string name, const int is_organic)
: m_name(name),
  m_is_organic(is_organic),
  m_level(1)
{
	init(is_organic);
}

Hero::~Hero()
{
	clearMoves();
}

void Hero::readSaveData(const std::string filename, const int dir, const bool debug)
{
	FileSystem* fs = FileSystem::get();
	heroSaveData* data = fs->parseHeroData(filename, dir, debug);

	setName(data->m_name);
	setNickname(data->m_nickname);

	for(int i = 0; i < NUM_STATS; i++) setStat(i, data->m_stats[i]);
	for(int i = 0; i < NUM_STATS; i++) setChancesSlot(i, data->m_stat_chances[i]);

	setLevel(data->m_level);
	setLevelReq(data->m_level_req);
	setCanHeal(data->m_can_heal_from_damage == 1);
	setOrganic(data->m_is_organic);
	init(m_is_organic);

	for(auto p = data->m_powers_id.begin(); p != data->m_powers_id.end(); ++p) addPower(powers[*p], false);

	for(int i = 0; i < MAX_MOVES; i++) 
	{
		if(data->m_moves_id[i] != -1)
		{
			addMove(*g_moves[data->m_moves_id[i]]);
		}
	}

	for(int i = 0; i < MAX_MOVES; i++) 
	{
		if(data->m_uses[i] != -1)
		{
			Move* move = getMove(i);
			move->setUses(data->m_uses[i]);
		}
	}

	for(int i = 0; i < MAX_MOVES; i++) 
	{
		if(data->m_lims[i] != -1)
		{
			Move* move = getMove(i);
			move->setLim(data->m_lims[i]);
		}
	}

	for(int i = 0; i < MAX_MOVES; i++) 
	{
		if(data->m_proficiencies[i] != -1)
		{
			Move* move = getMove(i);
			move->setProficiency(data->m_proficiencies[i]);
		}
	}

	setGender(data->m_is_female == FEMALE_INT);
	setEyeColor(data->m_eye_id);
	setHairColor(data->m_hair_id);
	setOrigin(data->m_origin_id);
	setMartialStatus(data->m_martial_status);
	setFeet(data->m_feet);
	setInches(data->m_inches);
	setWeight(data->m_weight);
	setAge(data->m_age);
	setYear(data->m_year);
	setDay(data->m_day);

	setMonth(data->m_month_str);
	setBirthplace(data->m_birth_place);
	setDescription(data->m_description_str);
}

void Hero::saveData(const std::string filename, const int dir)
{
	FileSystem *fs = FileSystem::get();
	heroSaveData data = {};

	data.m_name = getName();
	data.m_nickname = getNickname();

	for(int i = 0; i < NUM_STATS; i++) data.m_stats[i] = getStat(i);
	for(int i = 0; i < NUM_STATS; i++) data.m_stat_chances[i] = getChance(i);

	data.m_level = getLevel();
	data.m_level_req = getLevelReq();
	data.m_can_heal_from_damage = canHealFromDamage() ? 1 : 0;
	data.m_is_organic = getOrganic();

	for(auto p = m_powers.begin(); p != m_powers.end(); ++p) data.m_powers_id.push_back((*p)->m_id);

	for(int i = 0; i < MAX_MOVES; i++)
	{
		if(m_moves[i] != NULL) data.m_moves_id[i] = m_moves[i]->getID();
		else data.m_moves_id[i] = -1;
	}

	for(int i = 0; i < MAX_MOVES; i++)
	{
		if(m_moves[i] != NULL) data.m_uses[i] = m_moves[i]->getUses();
		else data.m_uses[i] = -1;
	}

	for(int i = 0; i < MAX_MOVES; i++)
	{
		if(m_moves[i] != NULL) data.m_lims[i] = m_moves[i]->getLim();
		else data.m_lims[i] = -1;
	}

	for(int i = 0; i < MAX_MOVES; i++)
	{
		if(m_moves[i] != NULL) data.m_proficiencies[i] = m_moves[i]->getProficiency();
		else data.m_proficiencies[i] = -1;
	}

	data.m_is_female = getGender() ? FEMALE_INT : MALE_INT;

	data.m_eye_id = getEyeColorID();
	data.m_hair_id = getHairColorID();
	data.m_origin_id = getOriginID();
	data.m_martial_status = getMartialStatusID();
	data.m_feet = getFeet();
	data.m_inches = getInches();
	data.m_weight = getWeight();
	data.m_age = getAge();
	data.m_year = getYear();
	data.m_month = getMonth();
	data.m_day = getDay();

	data.m_month_str = getMonthStr();
	data.m_birth_place = getBirthplace();
	data.m_description_str = getDescription();

	fs->writeHeroData(filename, data, dir);
}

void Hero::init(const int is_organic)
{
	switch(is_organic)
	{
		case ORGANIC_TYPE:
		{
			addAttribute(g_attributes[ORGANIC]);
		}
		break;
		case MECHANICAL_TYPE:
		{
			addAttribute(g_attributes[MECHANICAL]);
		}
		break;
		case BIO_MECHANICAL_TYPE:
		{
			addAttribute(g_attributes[ORGANIC]);
			addAttribute(g_attributes[MECHANICAL]);
		}
		break;
	}
}

void Hero::clearMoves()
{
	int times = m_num_moves;

	for(int i = 0; i < times; i++)
	{
		removeMove(0);
	}
}

void Hero::updateMoveset()
{
	//clearMoves();

	for(auto p = m_powers.begin(); p != m_powers.end(); ++p)
	{
		Power *power = *p;

		for(auto m = power->m_moves.begin(); m != power->m_moves.end(); ++m)
		{
			Move *move = *m;

			if(move->getLevelReq() == m_level) addMove(*move, (m_level > 1));
		}
	}
}

void Hero::moveReplacePrompt(const Move& move)
{
	using namespace e_std;

	std::string str1 = getName() + " can learn a new move... " + move.getName() +", but you have too many already.\nWhich would you like to replace?(10 - to decline)\n";
	std::string str2 = getName() + " choose not to learn " + move.getName();
	bool valid = false;

	while(!valid)
	{
		printMoves();
		int choice = loopAccept(str1, "", NULL, ACCEPT_INT);

		if(choice == 10)
		{
			println(str2);
			valid = true;
		}
		else if(choice < MAX_MOVES)
		{
			removeMove(choice);
			addMove(move);
			valid = true;
		}
	}
}

void Hero::addMove(const Move& move, const bool display)
{
	if(m_num_moves < MAX_MOVES)
	{
		Move *new_move = new Move(move);
		m_moves[m_num_moves++] = new_move;

		if(display) e_std::println("New move learned: " +move.getName()+ "!");
	}
	else
	{
		moveReplacePrompt(move);
	}
}

void Hero::removeMove(const int slot)
{
	if(m_num_moves > slot)
	{
		delete m_moves[slot];
		m_moves[slot] = NULL;

		updateMoveSlots(m_num_moves - 1);
	}	
}

void Hero::updateMoveSlots(const int curr_slots)
{
	int moves_found = 0;
	int empty_spot = -1;

	for(int i = 0; i < MAX_MOVES; i++)
	{
		if(m_moves[i] == NULL)
		{
			empty_spot = i;
		}
		else
		{
			if(empty_spot != -1)
			{
				m_moves[empty_spot] = m_moves[i];
				m_moves[i] = NULL;
				empty_spot = -1;
				i = 0;
			}

			moves_found++;
		}
	}

	m_num_moves = curr_slots;
}

void Hero::updateStats()
{
	updateBonusStats();
	updateStatTotal();
}

void Hero::printStatLine(const int stat)
{
	e_std::print(getStatString(stat) + ": " + std::to_string(m_stats[stat])); 
	e_std::setFore(FORE_GREEN);//, BACK_BLACK);
	e_std::print("  +(" + std::to_string(getStatBonus(stat)) + ")");
	e_std::resetText();
	e_std::print("              Total " + getStatString(stat) + ": ");
	e_std::setFore(FORE_GREEN);//, BACK_BLACK);
	e_std::setTextAppearance(BOLD);
	e_std::println("" + std::to_string(getStatTotal(stat)));
	e_std::resetText();
}

void Hero::printMoves(const bool combat)
{
	using namespace e_std;

	println("Move(s): ");
	setFore(FORE_YELLOW);//, BACK_BLACK);
	for(int i = 0; i < m_num_moves; i++)
	{
		Move* move = m_moves[i];

		print(std::to_string(i) + ": "); 
		if(!combat) move->printStats();
		else move->printCombatStats();
		println("");
	}
	resetText();
}

void Hero::printStats()
{
	using namespace e_std;

	updateStats();

	setFore(FORE_MAGENTA);//, BACK_BLUE);
	println("===============BASIC INFO==============");
	resetText();

	print("Name: ");
	setFore(FORE_CYAN);
	println(m_name);
	resetText();

	println("Level: " + std::to_string(m_level));
	print("Power(s): ");
	setFore(FORE_GREEN);//, BACK_BLACK);
	for(auto p = m_powers.begin(); p != m_powers.end(); ++p)
	{
		Power* pow = *p;


		print(" [" + pow->m_name + "] ");

	}
	resetText();
	println("");

	println("Attribute(s): ");
	setFore(FORE_BLUE);//, BACK_BLACK);

	for(auto a = m_attr.begin(); a != m_attr.end(); ++a)
	{
		Attribute* attr = *a;

		print( " [" + attr->m_name + "] ");
	}

	resetText();
	println("");

	printMoves();

	setFore(FORE_CYAN);//, BACK_BLUE);
	println("===============BASIC STATS=============");
	resetText();

	printStatLine(HEALTH);
	printStatLine(SPEED);
	printStatLine(AGILITY);
	printStatLine(SKILL);

	setFore(FORE_GREEN);//, BACK_BLUE);
	println("===============OFFENSIVE STATS=========");
	resetText();

	printStatLine(P_STR);
	printStatLine(E_STR);
	printStatLine(S_STR);

	setFore(FORE_YELLOW);//, BACK_BLUE);
	println("===============DEFENSIVE STATS=========");
	resetText();

	printStatLine(P_DUR);
	printStatLine(E_DUR);
	printStatLine(S_DUR);

	setFore(FORE_RED);//, BACK_BLACK);
	println("===============COMBAT STATS============");
	resetText();

	print("Hit Bonus: ");
	setFore(FORE_RED);//, BACK_BLACK);
	println(std::to_string(getHitChanceBonus()));
	resetText();

	print("Dodge Bonus: ");
	setFore(FORE_RED);//, BACK_BLACK);
	println(std::to_string(getDodgeChanceBonus()));
	resetText();

	print("Crit Bonus: ");
	setFore(FORE_RED);//, BACK_BLACK);
	println(std::to_string(getCritChanceBonus()));
	resetText();
}

void Hero::printDescription()
{

}

double Hero::getChanceToHit(Hero& defender, Move* move)
{
	double chance_bonus = (getHitChanceBonus() + move->getHitChance()) - defender.getDodgeChanceBonus();
	
	double hit_factor = getStatTotal(AGILITY) / (double) defender.getStatTotal(AGILITY);
	double hit_chance = (hit_factor / 2) * 100;

	return (hit_chance + chance_bonus);
}

int Hero::getChanceToCrit(Hero& defender, Move* move)
{
	return (getCritChanceBonus() + move->getCrit());
}

int Hero::getEffectiveDefenseStat(const int damage_type)
{
	switch(damage_type)
	{
		case PHYSICAL:
		{
			return P_DUR;
		}
		case ENERGY_TYPE:
		{
			return E_DUR;
		}
		case SPECIAL:
		{
			return S_DUR;
		}
	}
}

int Hero::getEffectiveOffensiveStat(const int damage_type)
{
	switch(damage_type)
	{
		case PHYSICAL:
		{
			return P_STR;
		}
		case ENERGY_TYPE:
		{
			return E_STR;
		}
		case SPECIAL:
		{
			return S_STR;
		}
	}
}

Move* Hero::selectMovePrompt()
{
	using namespace e_std;
	printMoves(true);
	int input = acceptIntln("Select which move?", 0, m_num_moves - 1);

	return getMove(input);
}

void Hero::setChances(const int health, const int speed, const int agility, const int skill, const int p_str, const int e_str, const int s_str, const int p_dur, const int e_dur, const int s_dur)
{
	m_stat_chances[HEALTH] = health;
	m_stat_chances[SPEED] = speed;
	m_stat_chances[AGILITY] = agility;
	m_stat_chances[SKILL] = skill;

	m_stat_chances[P_STR] = p_str;
	m_stat_chances[E_STR] = e_str;
	m_stat_chances[S_STR] = s_str;

	m_stat_chances[P_DUR] = p_dur;
	m_stat_chances[E_DUR] = e_dur;
	m_stat_chances[S_DUR] = s_dur;
}

void Hero::levelUp()
{
	using namespace e_std;

	m_level++;
	setNewReq();

	println("New Level: " + std::to_string(m_level));

	int basic_points = BASIC_LEVEL_POINTS; 
	int offensive_points = OFFENSIVE_LEVEL_POINTS;
	int defensive_points = DEFENSIVE_LEVEL_POINTS;

	for(int i = 0; i < basic_points; i++)
	{
		int basic_chance = randInt(0, 101);
		int basic_total = 0;

		for(int s = HEALTH; s < P_STR; s++)
		{
			basic_total += m_stat_chances[s];

			if(basic_chance <= basic_total)
			{
				addStat(s, 1);
				println("+1 " + getStatString(s));// << "\n";
				break;
			}
		}
	}

	for(int i = 0; i < offensive_points; i++)
	{
		int offensive_chance = randInt(0, 101);
		int offensive_total = 0;

		for(int s = P_STR; s < P_DUR; s++)
		{
			offensive_total += m_stat_chances[s];

			if(offensive_chance <= offensive_total)
			{
				addStat(s, 1);
				println("+1 " + getStatString(s));
				break;
			}
		}
	}

	for(int i = 0; i < defensive_points; i++)
	{
		int defensive_chance = randInt(0, 101);
		int defensive_total = 0;

		for(int s = P_DUR; s < NUM_STATS; s++)
		{
			defensive_total += m_stat_chances[s];

			if(defensive_chance <= defensive_total)
			{
				addStat(s, 1);
				println("+1 " + getStatString(s));
				break;
			}
		}
	}

	updateMoveset();
	updateStatTotal();
}

std::string Hero::doHeal(Hero& healer, Move* move, const bool debug)
{
	using namespace e_std;
	int times = move->getTimes();// + ((attacker.getStatTotal(SPEED) - getStatTotal(SPEED)) / ATTACKS_PER_SPEED);
	//bool afflict = randInt(0, 101) < move->getAlignmentChance();
	//bool hit_once = false;
	std::string battle_str = "----------------------------------------------\n" 
	+ healer.getName() + " fortified " + getName() + " " + std::to_string(times) + " time(s), using " + move->getName() + "\n";

	for(int i = 0; i < times; i++)
	{
		double hit_chance = move->getHit();
		bool hit = randInt(0, 101) < hit_chance;
		//if(hit) hit_once = true;

		int crit_skill = (healer.getStatTotal(SKILL));
		bool crit = randInt(0, 101) < (move->getCrit() + crit_skill);

		if(debug)
		{
			println("Hit Chance: " + std::to_string(hit_chance));
			println("Hit: " + std::to_string(hit));
			println("Crit Skill Roll: " + std::to_string(crit_skill));
			println("Crit Chance: " + std::to_string((healer.getCritChanceBonus() + move->getCrit())));
			println("Crit: " + std::to_string(crit));
		} 

		if(hit)
		{
			std::vector<AttackType *> attack_types = move->getTypes();
			double percent_modifier;

			//Removed for now
			int skill_roll = 0;//randInt(0, getStatTotal(SKILL));
			int damage = (move->getStat(HEALTH));// + skill_roll;

			if(debug)
			{
				println("Base Damage: " + std::to_string(damage));
				println("Skill Roll: " + std::to_string(skill_roll));
			}

			for(auto a = attack_types.begin(); a != attack_types.end(); ++a)
			{
				AttackType *type = *a;
				const int attack_id = type->m_id;
				percent_modifier += healer.getEffectiveDamageOutput(attack_id) - getEffectiveDamageReduction(attack_id);
				
				int damage_effectiveness = getEffectiveDamageReduction(attack_id);
				int bonus = healer.getEffectiveDamageOutput(attack_id);

				std::string effective_str = std::to_string(damage_effectiveness) + "% ineffective";
				std::string bonus_str = std::to_string(bonus) + "% more powerful";

				if(debug)
				{
					println("Current Attack Type: " + type->m_name);
					println(healer.getName() + " Damage Output: "  + std::to_string(healer.getEffectiveDamageOutput(attack_id)));
					println(getName() + " Damage Reduction: " + std::to_string(getEffectiveDamageReduction(attack_id)));
					println("Percent Modifier changed to: " + std::to_string(percent_modifier));
				}

				/*const int damage_type = type->m_damage_type;
				const int attacker_attack_stat = defender.getStatTotal(defender.getEffectiveOffensiveStat(damage_type));
				const int defender_defense_stat = getStatTotal(getEffectiveDefenseStat(damage_type));

				int effective_defense_stat = defender_defense_stat - move->getPiercing();
				effective_defense_stat = effective_defense_stat < 0 ? 0 : effective_defense_stat;

				damage += attacker_attack_stat - (effective_defense_stat);

				if(debug)
				{
					println("Current Damage Type: " + getDamageTypeString(damage_type));
					println(attacker.getName() + " " + getStatString(attacker.getEffectiveOffensiveStat(damage_type)) + "  Stat: " + std::to_string(attacker_attack_stat));
					println(getName() + " " + getStatString(getEffectiveDefenseStat(damage_type)) + " Stat: "  + std::to_string(defender_defense_stat));
					println(move->getName() + " Piercing: " + std::to_string(move->getPiercing()));
				}*/

				battle_str += move->getName() + "'s " + type->m_name + " type is " + effective_str + " and " + bonus_str + ".\n";
				//battle_str += "This moves uses " + attacker.getName() +"'s " + std::to_string(attacker_attack_stat) + " " + getStatString(attacker.getEffectiveOffensiveStat(damage_type)) + " and " + getName() + "'s " + std::to_string(defender_defense_stat) + " " + getStatString(getEffectiveDefenseStat(damage_type)) + ".\n";
				//if(move->getPiercing() > 0) battle_str += "That move pierced through!\n";
			}

			percent_modifier /= 100;
			//if((int)move->getIgnore() != 0) battle_str += move->getName() + " ignored " + std::to_string(move->getIgnore() * 100) + "% of " + getName() + "'s defense.\n";

			damage += damage * percent_modifier;
			//if(!m_can_heal_from_damage) damage = damage < 0 ? 0 : damage;

			if(crit)
			{
				damage *= CRIT_BONUS;
				battle_str += "Critical Heal!\n";
			} 

			damage += damage != 0 ? skill_roll : 0; 

			int last_health = getStatTotal(HEALTH);
			applyDamage(damage * -1);
			move->emit(battle_str);
	//		battle_str += healer.getName() + " dealt " + std::to_string(damage) + " damage to " + getName() + "\n";
			if(last_health != getStatTotal(HEALTH)) battle_str += getName() + "'s health changed from " + std::to_string(last_health) +" to " + std::to_string(getStatTotal(HEALTH))+ "\n";

			for(int i = SPEED; i < NUM_STATS; i++)
			{
				int diff = move->getStat(i);

				if(move->getStat(i) != 0)
				{
					diff += skill_roll;
					battle_str += getName() + "'s " + getStatString(i) + " was changed from " + std::to_string(getStatTotal(i)) + " to "+ std::to_string(getStatTotal(i) + diff) +".\n";		
				} 
				addStatTotal(i, diff);
			}

			if(debug)
			{
				println("Total Damage: " + std::to_string(damage));
				println("Ignore Percent: " + std::to_string(move->getIgnore()));
			}
		}
		else
		{
			battle_str += healer.getName() + " failed!\n";
		}
	}

	/*if(afflict && hit_once)
	{
		if(debug) println("Effect Added!");
		const StatusEffect* effect = move->getRandomEffect();
		addEffect(effect);
		battle_str += getName() + " got " + effect->m_name + "!\n";
	} */

	move->use();
	//println(battle_str);
	return battle_str;
}

void Hero::applyEffect(const StatusEffect *effect)
{
		addStatTotal(HEALTH, effect->m_effected_stats[HEALTH]);
		addStatTotal(SPEED, effect->m_effected_stats[SPEED]);
		addStatTotal(AGILITY, effect->m_effected_stats[AGILITY]);
		addStatTotal(SKILL, effect->m_effected_stats[SKILL]);

		addStatTotal(P_STR, effect->m_effected_stats[P_STR]);
		addStatTotal(E_STR, effect->m_effected_stats[E_STR]);
		addStatTotal(S_STR, effect->m_effected_stats[S_STR]);

		addStatTotal(P_DUR, effect->m_effected_stats[P_DUR]);
		addStatTotal(E_DUR, effect->m_effected_stats[E_DUR]);
		addStatTotal(S_DUR, effect->m_effected_stats[S_DUR]);
}

std::string Hero::doMove(Hero& attacker, Move* move, const bool debug)
{
	using namespace e_std;
	int speed_diff = ((attacker.getStatTotal(SPEED) - getStatTotal(SPEED)) / ATTACKS_PER_SPEED);
	speed_diff = speed_diff < 0 ? 0 : speed_diff;

	int times = move->getTimes() + speed_diff;
	bool afflict = randInt(0, 101) < move->getAlignmentChance();
	bool hit_once = false;
	std::string battle_str = "----------------------------------------------\n" 
	+ attacker.getName() + " attacked " + getName() + " " + std::to_string(times) + " time(s), using " + move->getName() + "\n";

	for(int i = 0; i < times; i++)
	{
		double hit_chance = attacker.getChanceToHit(*this, move);
		bool hit = randInt(0, 101) < hit_chance;
		if(hit) hit_once = true;

		int crit_skill = (getStatTotal(SKILL) - (attacker.getStatTotal(SKILL)/2));
		crit_skill = crit_skill < 0 ? 0 : crit_skill;

		bool crit = randInt(0, 101) < ((attacker.getCritChanceBonus() + move->getCrit()) - crit_skill);

		if(debug)
		{
			println("Hit Chance: " + std::to_string(hit_chance));
			println("Hit: " + std::to_string(hit));
			println("Crit Skill Roll: " + std::to_string(crit_skill));
			println("Crit Chance: " + std::to_string((attacker.getCritChanceBonus() + move->getCrit())));
			println("Crit: " + std::to_string(crit));
		} 

		if(hit)
		{
			std::vector<AttackType *> attack_types = move->getTypes();
			double percent_modifier;

			//Skill roll never retracts from damage
			int skill_roll = (randInt(0, attacker.getStatTotal(SKILL)) - randInt(0, getStatTotal(SKILL)));
			skill_roll = skill_roll < 0 ? 0 : skill_roll;

			int damage = (move->getStat(HEALTH) * -1) + skill_roll;

			if(debug)
			{
				println("Base Damage: " + std::to_string(damage));
				println("Skill Roll: " + std::to_string(skill_roll));
			}

			for(auto a = attack_types.begin(); a != attack_types.end(); ++a)
			{
				AttackType *type = *a;
				const int attack_id = type->m_id;
				percent_modifier += attacker.getEffectiveDamageOutput(attack_id) - getEffectiveDamageReduction(attack_id);
				
				int damage_effectiveness = getEffectiveDamageReduction(attack_id);
				int bonus = attacker.getEffectiveDamageOutput(attack_id);

				std::string effective_str = std::to_string(damage_effectiveness) + "% effective";
				std::string bonus_str = std::to_string(bonus) + "% more powerful";

				if(debug)
				{
					println("Current Attack Type: " + type->m_name);
					println(attacker.getName() + " Damage Output: "  + std::to_string(attacker.getEffectiveDamageOutput(attack_id)));
					println(getName() + " Damage Reduction: " + std::to_string(getEffectiveDamageReduction(attack_id)));
					println("Percent Modifier changed to: " + std::to_string(percent_modifier));
				}

				const int damage_type = type->m_damage_type;
				const int attacker_attack_stat = attacker.getStatTotal(attacker.getEffectiveOffensiveStat(damage_type));
				const int defender_defense_stat = getStatTotal(getEffectiveDefenseStat(damage_type));

				int effective_defense_stat = defender_defense_stat - move->getPiercing();
				effective_defense_stat = effective_defense_stat < 0 ? 0 : effective_defense_stat;

				damage += attacker_attack_stat - (effective_defense_stat);

				if(debug)
				{
					println("Current Damage Type: " + getDamageTypeString(damage_type));
					println(attacker.getName() + " " + getStatString(attacker.getEffectiveOffensiveStat(damage_type)) + "  Stat: " + std::to_string(attacker_attack_stat));
					println(getName() + " " + getStatString(getEffectiveDefenseStat(damage_type)) + " Stat: "  + std::to_string(defender_defense_stat));
					println(move->getName() + " Piercing: " + std::to_string(move->getPiercing()));
				}

				battle_str += move->getName() + "'s " + type->m_name + " type is " + effective_str + " and " + bonus_str + ".\n";
				battle_str += "This moves uses " + attacker.getName() +"'s " + std::to_string(attacker_attack_stat) + " " + getStatString(attacker.getEffectiveOffensiveStat(damage_type)) + " and " + getName() + "'s " + std::to_string(defender_defense_stat) + " " + getStatString(getEffectiveDefenseStat(damage_type)) + ".\n";
				if(move->getPiercing() > 0) battle_str += "That move pierced through!\n";
			}

			percent_modifier += move->getIgnore();
			percent_modifier /= 100;
			if((int)move->getIgnore() != 0) battle_str += move->getName() + " ignored " + std::to_string(move->getIgnore() * 100) + "% of " + getName() + "'s defense.\n";

			damage += damage * percent_modifier;
			if(!m_can_heal_from_damage) damage = damage < 0 ? 0 : damage;

			if(crit)
			{
				damage *= CRIT_BONUS;
				battle_str += "Critical Hit!\n";
			} 

			int last_health = getStatTotal(HEALTH);
			applyDamage(damage);
			move->emit(battle_str);
			battle_str += attacker.getName() + " dealt " + std::to_string(damage) + " damage to " + getName() + "\n";
			if(last_health != getStatTotal(HEALTH)) battle_str += getName() + "'s health changed from " + std::to_string(last_health) +" to " + std::to_string(getStatTotal(HEALTH))+ "\n";

			for(int i = SPEED; i < NUM_STATS; i++)
			{
				addStatTotal(i, move->getStat(i));
				if(move->getStat(i) != 0) battle_str += getName() + "'s " + getStatString(i) + " was affected by a total of " + std::to_string(move->getStat(i)) + ".\n";
			}

			if(debug)
			{
				println("Total Damage: " + std::to_string(damage));
				println("Ignore Percent: " + std::to_string(move->getIgnore()));
			}
		}
		else
		{
			battle_str += attacker.getName() + " missed!\n";
		}
	}

	if(afflict && hit_once)
	{
		if(debug) println("Effect Added!");
		const StatusEffect* effect = move->getRandomEffect();
		addEffect(effect);
		battle_str += getName() + " got " + effect->m_name + "!\n";
	} 

	move->use();
	//println(battle_str);
	return battle_str;
}

void Hero::addPower(Power* power, const bool update)
{
	for(auto a = power->m_attr.begin(); a != power->m_attr.end(); ++a)
	{
		addAttribute(*a);

		if((*a)->m_heal_from_damage) m_can_heal_from_damage = true; 
	}

	m_powers.push_back(power);
	if(update) updateMoveset();
}

int Hero::getHitChanceBonus()
{
	int hit_increase = 0;

	for(auto attr_iter = m_attr.begin(); attr_iter != m_attr.end(); attr_iter++)
	{
		Attribute *attr = *attr_iter;

		hit_increase += attr->m_hit_chance;
	}

	return hit_increase;
}

int Hero::getDodgeChanceBonus()
{
	int dodge_increase = 0;

	for(auto attr_iter = m_attr.begin(); attr_iter != m_attr.end(); attr_iter++)
	{
		Attribute *attr = *attr_iter;

		dodge_increase += attr->m_dodge_chance;
	}

	return dodge_increase;
}

int Hero::getCritChanceBonus()
{
	int crit_increase = 0;

	for(auto attr_iter = m_attr.begin(); attr_iter != m_attr.end(); attr_iter++)
	{
		Attribute *attr = *attr_iter;

		crit_increase += attr->m_crit_chance;
	}

	return crit_increase;
}

int Hero::getEffectiveDamageOutput(const int attack_type) 
{
	int damage_increase = 0;

	for(auto attr_iter = m_attr.begin(); attr_iter != m_attr.end(); attr_iter++)
	{
		Attribute *attr = *attr_iter;

		damage_increase += attr->m_attack_type_bonus[attack_type];
	}

	return damage_increase;
}

int Hero::getEffectiveDamageReduction(const int attack_type) 
{
	int damage_decrease = 0;

	for(auto attr_iter = m_attr.begin(); attr_iter != m_attr.end(); attr_iter++)
	{
		Attribute *attr = *attr_iter;

		damage_decrease += attr->m_attack_type_reduction[attack_type];
	}

	return damage_decrease;
}


void Hero::updateBonusStats()
{
	clearBonusStats();

	for(auto attr_iter = m_attr.begin(); attr_iter != m_attr.end(); attr_iter++)
	{
		Attribute *attr = *attr_iter;

		for(int i = 0; i < NUM_STATS; i++)
		{
			m_bonus_stats[i] += attr->m_stat_bonus[i];
		}
	}
}
void Hero::updateStatTotal()
{
	for(int i = 0; i < NUM_STATS; i++)
	{
		m_total_stats[i] = m_bonus_stats[i] + m_stats[i];
	}
}

void Hero::set(const int health, const int speed, const int agility, const int skill, const int p_str, const int e_str, const int s_str, const int p_dur, const int e_dur, const int s_dur)
{
	m_stats[HEALTH] = health;
	m_stats[SPEED] = speed;
	m_stats[AGILITY] = agility;
	m_stats[SKILL] = skill;

	m_stats[P_STR] = p_str;
	m_stats[E_STR] = e_str;
	m_stats[S_STR] = s_str;

	m_stats[P_DUR] = p_dur;
	m_stats[E_DUR] = e_dur;
	m_stats[S_DUR] = s_dur;
}

void Hero::add(const int health, const int speed, const int agility, const int skill, const int p_str, const int e_str, const int s_str, const int p_dur, const int e_dur, const int s_dur)
{
	m_stats[HEALTH] += health;
	m_stats[SPEED] += speed;
	m_stats[AGILITY] += agility;
	m_stats[SKILL] += skill;

	m_stats[P_STR] += p_str;
	m_stats[E_STR] += e_str;
	m_stats[S_STR] += s_str;

	m_stats[P_DUR] += p_dur;
	m_stats[E_DUR] += e_dur;
	m_stats[S_DUR] += s_dur;
}

void Hero::setMonth(std::string month_str)
{ 
	m_month_str = month_str; 

	for(int i = 0; i < num_months; i++)
	{
		if(months[i].find(month_str))
		{
			m_month = i;
		}
	}
}

void Hero::savePrompt()
{
	FileSystem* fs = FileSystem::get();
	std::string filename = fs->promptFilename("What should the file be named?");

	saveData(filename, CUSTOM_DIR);
}

void Hero::readPrompt(const bool debug)
{
	FileSystem* fs = FileSystem::get();
	std::string filename = fs->promptFilename("What is the file name?");

	readSaveData(filename, CUSTOM_DIR, debug);
}

void Hero::fillOutCharacter()
{
	using namespace e_std;
	std::string first_name, last_name;
	store("What is the first name of this character?\n", &first_name);
	store("What is the last name of this character?\n", &last_name);
	store("What will this character's superhero name be?\n", &m_nickname);

	setName(first_name + " " +last_name);

	for(int i = 0; i < NUM_STATS; i++) 
	{
		setStat(i, acceptIntln("How much "+getStatString(i)+"?", NO_RANGE, NO_RANGE));
	}

	for(int i = 0; i < NUM_STATS; i++) 
	{
		int choice = acceptIntln("How much weight should "+getStatString(i)+" have?", NO_RANGE, NO_RANGE);
		setChancesSlot(i, choice);
	}

	setLevel(acceptIntln("Level?", NO_RANGE, NO_RANGE));
	setLevelReq(acceptIntln("Level Req?", NO_RANGE, NO_RANGE));
	setCanHeal(acceptIntln("Can heal from certain types of damage?(1 - yes, 0 - no)", 0, 1) == 1);
	setOrganic(acceptIntln("Are they are organic?(0 - organic, 1 - mechanical, 2 - bio-mechanical)", 0, 2));
	init(m_is_organic);

	bool valid = false;
	while(!valid)
	{
		listPowers();
		int id = acceptIntln("Which power should they have?(-1 to stop)", -1, NUM_POWERS - 1);
		
		if(id == -1) valid = true;
		else if(id < NUM_POWERS)
		{
			addPower(powers[id]);	
			valid = true;
		} 
	}

	setGender(acceptIntln("What Gender?(1 for female, 0 for male)", 0, 1) == FEMALE_INT);

	listEyeColors();
	setEyeColor(acceptIntln("Which eye color code?", 0, NUM_EYE_COLORS - 1));

	listHairColors();
	setHairColor(acceptIntln("Which hair color code?", 0, NUM_HAIR_COLORS - 1));

	listOrigins();
	setOrigin(acceptIntln("Which origin code?", 0, NUM_ORIGINS - 1));

	listMartialStatuses();
	setMartialStatus(acceptIntln("Which martial status code?", 0, NUM_MARTIAL_STATUS - 1));

	setFeet(acceptIntln("How tall?(In feet)", NO_RANGE, NO_RANGE));
	setInches(acceptIntln("How tall?(In Inches)", NO_RANGE, NO_RANGE));
	setWeight(acceptIntln("How much do they weight?(lbs)", NO_RANGE, NO_RANGE));
	setAge(acceptIntln("How old are they?", NO_RANGE, NO_RANGE));
	setYear(acceptIntln("What year were they born?", NO_RANGE, NO_RANGE));
	setDay(acceptIntln("What day were they born?", NO_RANGE, NO_RANGE));

	store("What month were they born in?\n", &m_month_str);
	store("Where were they born?\n", &m_birth_place);
	store("Any description/biography?\n", &m_description_str);

	bool save = acceptIntln("Save?(1 - yes, 0 - no)", 0, 1) == 1;

	if(save)
	{
		savePrompt();
	}
}

void Hero::randomizeStats(const bool super)
{
	m_is_female = e_std::randInt(0, 100) <= 50 ? true : false;
	setName(getRandomName(m_is_female));
	setStat(HEALTH, 20);
	setLevel(1);
	init();	

	for(int i = 0; i < START_LEVEL_POINTS; i++)
	{
		int stat = e_std::randInt(0, NUM_STATS);
		addStat(stat, 1);
	}

	setChances(25, 25, 25, 25, 33, 33, 33, 33, 33, 33);

	bool cont = true;

	while(cont)
	{
		Power* p = getRandomPower(super);
		bool has = hasPower(p);
		if(!has) addPower(p);
		cont = e_std::randInt(0, 101) < 5;
	}

	updateStats();
}

void listEyeColors()
{
	using namespace e_std;
	for(int i = 0; i < NUM_EYE_COLORS; i++)
	{
		println(std::to_string(i)+": "+eye_colors[i]);
	}
}

void listHairColors()
{
	using namespace e_std;
	for(int i = 0; i < NUM_HAIR_COLORS; i++)
	{
		println(std::to_string(i)+": "+hair_colors[i]);
	}
}

void listOrigins()
{
	using namespace e_std;
	for(int i = 0; i < NUM_ORIGINS; i++)
	{
		println(std::to_string(i)+": "+origins[i]);
	}
}

void listMartialStatuses()
{
	using namespace e_std;
	for(int i = 0; i < NUM_MARTIAL_STATUS; i++)
	{
		println(std::to_string(i)+": "+martial_statuses[i]);
	}
}

std::string getRandomName(const bool is_female)
{
	using namespace e_std;

	if(is_female)
	{
		return hero_names_female[randInt(0, female_names)];
	}
	else
	{
		return hero_names_male[randInt(0, male_names)];
	}
}

Move* Hero::getRandomMove(const bool attack) 
{ 
	if(m_num_moves < 1) return NULL;
	Move* m = m_moves[0];
	int absorb = 0;

	for(int i = 0; i < m_num_moves; i++)
	{
		absorb += (101/m_num_moves);

		if(e_std::randInt(0, 101) < absorb)
		{
			m = m_moves[i];
			return m;
		}
	}

	return NULL;
}


/*void Hero::setEyeColor(std::string color) 
{
	for(int i = 0; i < NUM_EYE_COLORS; i++)
	{
		if(eye_colors[i].find(color) != std::string::npos)
		{
			m_eye_id = i;
		}
	}
}

void Hero::setHairColor(std::string color) 
{
	for(int i = 0; i < NUM_HAIR_COLORS; i++)
	{
		if(hair_colors[i].find(color) != std::string::npos)
		{
			m_hair_id = i;
		}
	}
}

void Hero::setOrigin(std::string origin) 
{
	for(int i = 0; i < NUM_ORIGINS; i++)
	{
		if(origins[i].find(origin) != std::string::npos)
		{
			m_origin_id = i;
		}
	}
}

void Hero::setMartialStatusColor(std::string status) 
{
	for(int i = 0; i < NUM_MARTIAL_STATUS; i++)
	{
		if(martial_statuses[i].find(status) != std::string::npos)
		{
			m_martial_status = i;
		}
	}
}*/
