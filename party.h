#ifndef PARTY_H
#define PARTY_H

#include "hero.h"

class Party
{
public:
	Party(std::string name);
	~Party() {}

	void addMember(Hero* hero) { m_members.push_back(hero); }
	Hero* getMember(const int index) { return m_members.at(index); }
	void removeMember(const int index) { if(index < m_members.size()) m_members.erase(m_members.begin() + index); }
	int getSize() { return m_members.size(); }

	std::string getName() const { return m_name; }
	void displayMembers(const bool update = false);
	bool isEmpty() { return m_members.empty(); }
	bool updateParty();

	bool doBattle(Party& party, const bool attack_back = false);
	void backup() { m_backup = m_members; }
	void restore() { m_members = m_backup; }
	void checkLevel();
	void updateMemberStats()
	{
		for(auto h = m_members.begin(); h != m_members.end(); ++h)
		{
			(*h)->updateStats();
		}
	}
private:
	std::string m_name;
	std::vector<Hero *> m_members;
	std::vector<Hero *> m_backup;

	void attack(Hero* attacker, Hero* defender, Party& party, Move* move);
	void updateCooldowns();
	void updateEffects(const int turn);
};

#endif