#ifndef OPTION_H
#define OPTION_H

#include <string>
#include "hero.h"


class Option
{
public:
	Option(std::string text) : m_text(text) {}
	virtual ~Option() {}

	virtual void execute() = 0;

	std::string getText() { return m_text; }
protected:
	const std::string m_text;
};

class StartOption : public Option
{
public:
	StartOption(std::string text) : Option(text) {}
	void execute() { /* Switch to main chapter*/ }
};

class ExitOption : public Option
{
public:
	ExitOption(std::string text) : Option(text) {}
	void execute() { exit(1); }
};

class BattleOption : public Option
{
public:
	BattleOption(std::string text) : Option(text) {}
	void execute() { /* Party battle code*/}
};

class DesignCharacterOption : public Option
{
public:
	DesignCharacterOption(std::string text) : Option(text) {}
	void execute() 
	{ 			
		Hero test_hero;
		test_hero.fillOutCharacter();
	}
};

#endif