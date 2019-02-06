#include "party.h"
#include "console.h"
#include "filesystem.h"

Party::Party(std::string name)
: m_name(name),
  m_members(0)
{

}

void Party::displayMembers(const bool update)
{
	using namespace e_std;

	setFore(FORE_BLUE);
	println("===============" + getName() + "===============");
	resetText();

	for(int i = 0; i < getSize(); i++)
	{
		fill(80, '-');
		println("");

		Hero* member = m_members.at(i);
		if(update) member->updateStats();

		print(std::to_string(i) + ": ");
		setFore(FORE_CYAN);
		print(member->getName());// << "\n";
		resetText();
		setFore(FORE_YELLOW);
		print(" " + member->getGenderSymbol());
		resetText();
		print(" Level: ");
		setFore(FORE_RED);
		println(std::to_string(member->getLevel()));
		resetText();


		println("Info: ");
		fill(5, ' ');
		setFore(FORE_GREEN);
		for(auto p = member->getPowers().begin(); p != member->getPowers().end(); ++p)
		{
			print("[" + (*p)->m_name + "] ");
		}
		resetText();
		println("");

		for(int i = 0; i < NUM_STATS; i++)
		{
			print("|"+getShortenStatString(i)+": ");
			setFore(FORE_GREEN);
			setTextAppearance(BOLD);
			print(std::to_string(member->getStatTotal(i)));
			resetText();
		}
		println("|");
	}
}

bool Party::updateParty()
{
	if(m_members.empty()) return true;
	for(int i = 0; i < m_members.size(); i++) 
	{
		if(m_members.at(i)->getStatTotal(HEALTH) <= 0)
		{
			m_members.erase(m_members.begin() + i);
		}
	}

	return false;
}

void Party::checkLevel()
{
	for(auto m = m_members.begin(); m != m_members.end(); ++m)
	{
		Hero *member = *m;

		member->checkProficiency();
	}
}

void Party::updateCooldowns()
{
	for(auto m = m_members.begin(); m != m_members.end(); ++m)
	{
		Hero *member = *m;
		if(!member->isAfflicted()) continue;

		for(int i = 0; i < member->getNumMoves(); i++)
		{
			Move* move = member->getMove(i);

			if(move->needsCooldown()) move->decrementCooldown();
		}
	}
}

void Party::updateEffects(const int turn)
{
	for(auto m = m_members.begin(); m != m_members.end(); ++m)
	{
		Hero *member = *m;

		for(int i = 0; i < member->getNumEffects(); i++)
		{
			const StatusEffect* effect = member->getEffect(i);

			if(turn % effect->m_rate == 0) member->applyEffect(effect);

			if(e_std::randInt(0, 101) <= effect->m_recover_chance)
			{
				member->removeEffect(i);
			}
		}
	}
}

bool Party::doBattle(Party& party, const bool attack_back)
{
	using namespace e_std;

	updateMemberStats();
	party.updateMemberStats();
	backup();

	bool in_battle = true;
	bool victory = false;
	int turn = 1;
	std::string battle_str = "";

	while(in_battle)
	{
		println("============================TURN: " + std::to_string(turn) + "============================");
		battle_str += "============================TURN: " + std::to_string(turn) + "============================\n";
		
		displayMembers();
		party.displayMembers();

		int choices[m_members.size()];
		Move* moves[m_members.size()];

		int e_choices[party.getSize()];
		Move* e_moves[party.getSize()];

		for(int i = 0; i < m_members.size(); i++)
		{
			Hero* member = m_members.at(i);

			choices[i] = acceptIntln("Who should "+ member->getName()+" attack?", 0, party.getSize() - 1);
			moves[i] = member->selectMovePrompt();

			if(moves[i]->needsCooldown())
			{
				println("Move still needs to cooldown! Cooldown Turns left: "+ std::to_string(moves[i]->getCooldown()));
				i--;
				continue;
			}

			if(!moves[i]->isAttack())
			{
				int member_choice = 0;
				choices[i] = -1;
				if(moves[i]->getEffected() == SELF_ONLY)
				{
					battle_str += member->doHeal(*member, moves[i]);
				}
				else
				{
					member_choice = acceptIntln("Who should "+ member->getName()+" heal on your team?", 0, m_members.size() - 1);
					Hero* other_member = m_members.at(member_choice);
					battle_str += other_member->doHeal(*member, moves[i]);
				}
			}
		}

		/*if(attack_back)
		{
			for(int i = 0; i < party.getSize(); i++)
			{
				Hero* member = party.getMember(i);

				e_choices[i] = randInt(0, party.getSize());
				e_moves[i] = enemy->getRandomMove();

				if(!e_moves[i]->isAttack())
				{
					int member_choice = 0;
					choices = -1;
					if(e_moves[i]->getEffected() == SELF_ONLY)
					{
						battle_str += member->doHeal(*member, e_moves[i]);
					}
					else
					{
						member_choice = randInt(0, party.getSize()); //acceptIntln("Who should "+ member->getName()+" heal on your team?");
						Hero* other_member = m_members.at(member_choice);
						battle_str += other_member->doHeal(*member, e_moves[i]);
					}
				}
			}
		}*/

		for (int i = 0; i < m_members.size(); ++i)
		{
			if(choices[i] == -1) continue;
			Hero* member = m_members.at(i);

			if(choices[i] >= party.getSize()) 
			{
				println("Invalid target for "+member->getName());
				continue;
			}

			Hero* enemy = party.getMember(choices[i]);
			battle_str += "============================" + member->getName() + " VS. " + enemy->getName() + "============================\n";

			int times = 0;
			while(times < 2)
			{
				bool m_first = (times == 0 ? member->getStatTotal(SPEED) >= enemy->getStatTotal(SPEED) : member->getStatTotal(SPEED) < enemy->getStatTotal(SPEED));// * member->getStatTotal(SPEED);
				if(m_first)
				{
					Move* m = moves[i];
					battle_str += enemy->doMove(*member, m);
					if(enemy->getStatTotal(HEALTH) <= 0) 
					{
						battle_str += enemy->getName() + " was defeated by " + member->getName() + ".\n";
						break;
					}
				}
				else 
				{
					Move* m = enemy->getRandomMove();


					if(m->needsCooldown())
					{
						battle_str += enemy->getName() + " is catching their breath.";
					}
					else
					{
						if(!m->isAttack())
						{
							int member_choice = 0;
							if(m->getEffected() == SELF_ONLY)
							{
								battle_str += enemy->doHeal(*enemy, m);
							}
							else
							{
								member_choice = randInt(0, party.getSize()); //acceptIntln("Who should "+ member->getName()+" heal on your team?");
								Hero* other_member = party.getMember(member_choice);
								battle_str += other_member->doHeal(*enemy, m);
							}
						}
						else
						{
							battle_str += member->doMove(*enemy, m);
						}
					}

					if(member->getStatTotal(HEALTH) <= 0)
					{
						battle_str += member->getName() + " was defeated by " + enemy->getName() + ".\n";
						break;
					}
				}

				times++;
			}

			party.updateParty();
			updateParty();

			if(party.isEmpty() || isEmpty()) break;
		}

		if(isEmpty())
		{
			in_battle = false;
		}
		else if(party.isEmpty())
		{
			victory = true;
			in_battle = false;
		}

		println(battle_str);

		updateEffects(turn);
		updateCooldowns();
		party.updateEffects(turn);
		party.updateCooldowns();
		
		turn++;
	}
	int save = acceptIntln("Save battle?(0 - no, 1 - yes)", 0, 1);
	
	if(save)FileSystem::get()->writeBattleString(battle_str);
	

	restore();
	checkLevel();
	updateMemberStats();
	return victory;
}

void Party::attack(Hero* attacker, Hero* defender, Party& party, Move* move)
{
	//defender->doMove(attacker, move);
	//party.updateParty();
	//updateParty();
}