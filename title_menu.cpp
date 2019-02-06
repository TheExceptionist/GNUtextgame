#include "title_menu.h"

TitleMenu::TitleMenu(std::string title, const int slots)
: Menu(title, slots)
{

}

void TitleMenu::update()
{
	printTitle();
	printOptions();

	int choice = e_std::acceptIntln("What option would you like to select?", 0, m_slots);
	Option* select_option = getOption(choice);

	select_option->execute();
}