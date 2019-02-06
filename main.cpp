

#include "hero.h"
#include "attack_type.h"
#include "console.h"
#include "party.h"
#include "option.h"
#include "title_menu.h"

Party* g_p_party;

void initParties()
{
	g_p_party = new Party("Player Party");
}

void deleteParties()
{
	delete g_p_party;
}

void initAll()
{
	srand(time(NULL));
	initStatusEffects();
	initAttackTypes();
	initAttributes();
	initMove();
	initPower();
	initParties();
}

void deleteAll()
{
	deleteParties();
	deletePower();
	deleteMove();
	deleteAttributes();
	deleteAttackTypes();
	deleteStatusEffects();
}

void partyTest()
{
	using namespace e_std;

	Party test_party("Test Party");

	Hero test_hero1;
	test_hero1.randomizeStats();

	Hero test_hero2;
	test_hero2.randomizeStats();
	test_hero2.levelUp();
	test_hero2.levelUp();
	test_hero2.levelUp();

	Hero test_hero3;
	test_hero3.randomizeStats();
	test_hero3.levelUp();
	test_hero3.levelUp();
	test_hero3.levelUp();
	test_hero3.levelUp();
	test_hero3.levelUp();

	Hero test_hero4;
	test_hero4.randomizeStats();

	Hero test_hero5;
	test_hero5.randomizeStats();

	Hero test_hero6;
	test_hero6.randomizeStats();

	g_p_party->addMember(&test_hero1);
	g_p_party->addMember(&test_hero2);
	g_p_party->addMember(&test_hero3);
	test_party.addMember(&test_hero4);
	test_party.addMember(&test_hero5);
	test_party.addMember(&test_hero6);


	g_p_party->displayMembers();
	acceptIntln("Continue?", 0, 1);

	//test_party.displayMembers();
	//bool p_win = g_p_party->doBattle(test_party);
	//println("Player Win: "+p_win);
	g_p_party->backup();
	g_p_party->removeMember(0);
	g_p_party->displayMembers();
	acceptIntln("Continue?", 0, 1);

	g_p_party->restore();
	g_p_party->displayMembers();
}

/*void miscTest()
{
		using namespace e_std;
	initAll();

	Hero hero("Rona");
	hero.set(20, 5, 5, 5, 5, 5, 5, 5, 5, 5);
	hero.setChances(25, 55, 10, 10,
	 90, 5, 5, 
	 90, 5, 5);
	hero.addPower(powers[SUPER_STRENGTH]);

	Hero dummy("Test Dummy");
	dummy.set(5, 5, 5, 5, 5, 5, 5, 5, 5, 5);
	
	hero.printStats();
	dummy.printStats();

	partyTest();

	while(g_running)
	{
		hero.printStats();
		dummy.printStats();

		int input;
		Move* m = hero.selectMovePrompt();

		if(m != NULL)
		{
			dummy.doMove(hero, m, true);
		}

		input = acceptIntln("Continue?(1 - yes, 0 - no)", 0, 1);

		while(input == 2)
		{
			hero.levelUp();
			input = acceptIntln("Again?(2 - yes, 1 - no)", 0, 1);
		}

		if(input == 3)
		{
			hero.savePrompt();

			Hero test_hero;
			test_hero.readPrompt(true);
			test_hero.printStats();

			input = 1;
		}

		if(input == 4)
		{
			Hero test_hero;
			test_hero.fillOutCharacter();
			test_hero.printStats();

			input = 1;
		}

		if(input == 5)
		{
			Hero test_hero;
			test_hero.randomizeStats();
			test_hero.printStats();

			input = 1;
		}


		g_running = (input == 1);
	}

	deleteAll();
}*/

bool g_running = true;

int main(int argc, char* argv[])
{
	initAll();

	StartOption start_option("Start");
	ExitOption exit_option("Exit");
	BattleOption battle_option("Quick Battle");
	DesignCharacterOption design_option("Design a Character");

	TitleMenu title("The Renegades", 4);
	title.addOption(&start_option);
	title.addOption(&battle_option);
	title.addOption(&design_option);
	title.addOption(&exit_option);

	Menu* curr_menu = &title;

	while(g_running)
	{
		curr_menu->update();
	}

	deleteAll();
	return 0;
}