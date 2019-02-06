#ifndef MENU_H
#define MENU_H

#include "option.h"
#include "console.h"

class Menu
{
public:
	Menu(std::string title, const int slots) : m_slots(slots), m_title(title) {}
	virtual ~Menu() {}

	virtual void update() = 0;

	void addOption(Option* option) { if(m_slots > m_num_options) { m_options.push_back(option); m_num_options++;} }
	Option* getOption(const int index) { return m_options.at(index); }

	void printOptions();
	void printTitle();
protected:
	const int m_slots; 
	int m_num_options = 0;

	std::string m_title;
	std::vector<Option*> m_options;
};

#endif