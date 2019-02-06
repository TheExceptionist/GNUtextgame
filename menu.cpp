#include "menu.h"

void Menu::printOptions()
{
	using namespace e_std;
	
	 for(int i = 0; i < m_options.size(); i++) 
	 {
	 	Option* opt = m_options.at(i);
	 	println(std::to_string(i)+": "+opt->getText());
	 }
}

void Menu::printTitle()
{
	using namespace e_std;

	print("============================");
	setFore(FORE_BLUE);
	print(m_title);
	resetText();
	println("============================");
}