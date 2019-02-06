#ifndef POWER_H
#define POWER_H

#include "move.h"
#include "attribute.h"

void initPower();
void deletePower();
void listPowers();

struct Power
{
	Power(const std::string name, const int id)
	: m_name(name),
	  m_id(id)
	{

	}

	void addAttribute(Attribute *attr) { m_attr.push_back(attr); }
	void addMove(Move *move) { m_moves.push_back(move); }

	const std::string m_name;
	const int m_id;
	std::vector<Attribute *> m_attr;
	std::vector<Move *> m_moves;
};

Power* getRandomPower(const bool super);
extern Power* powers[NUM_POWERS];

#endif