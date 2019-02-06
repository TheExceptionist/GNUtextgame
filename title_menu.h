#ifndef TITLE_MENU_H
#define TITLE_MENU_H

#include "menu.h"

class TitleMenu : public Menu
{
public:
	TitleMenu(std::string title, const int slots);
	virtual ~TitleMenu() {}

	virtual void update();
protected:
};

#endif