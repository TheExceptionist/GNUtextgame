#include "attribute.h"

Attribute* g_attributes[NUM_ATTRIBUTES];

void deleteAttributes()
{
	for(int i = 0; i < NUM_ATTRIBUTES; i++)
	{
		delete g_attributes[i];
	}
}


void initAttributes()
{
	g_attributes[ORGANIC] = new Attribute("Organic", 20, 10, 5);
	g_attributes[ORGANIC]->set(0, 1, 1, 1, 0, 0, 0, 0, 0, 0);
	g_attributes[ORGANIC]->m_attack_type_reduction[CUTTING] = -20;
	g_attributes[ORGANIC]->m_attack_type_reduction[DEATH] = -50;
	g_attributes[ORGANIC]->m_attack_type_reduction[BLOOD] = -100;
	g_attributes[ORGANIC]->m_attack_type_reduction[ACID] = -10;
	g_attributes[ORGANIC]->m_attack_type_reduction[POISON] = -30;
	g_attributes[ORGANIC]->m_attack_type_reduction[MIND] = -75;

	g_attributes[MECHANICAL] = new Attribute("Mechincal", 0, 0, 0);
	g_attributes[MECHANICAL]->set(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	g_attributes[MECHANICAL]->m_attack_type_reduction[CUTTING] = 75;
	g_attributes[MECHANICAL]->m_attack_type_reduction[PIERCING] = 25;
	g_attributes[MECHANICAL]->m_attack_type_reduction[DEATH] = 100;
	g_attributes[MECHANICAL]->m_attack_type_reduction[BLOOD] = 100;
	g_attributes[MECHANICAL]->m_attack_type_reduction[ACID] = -45;
	g_attributes[MECHANICAL]->m_attack_type_reduction[POISON] = 100;
	g_attributes[MECHANICAL]->m_attack_type_reduction[TIME] = -50;
	g_attributes[MECHANICAL]->m_attack_type_reduction[COMBUSTION] = -100;
	g_attributes[MECHANICAL]->m_attack_type_reduction[ELECTRIC] = -100;
	g_attributes[MECHANICAL]->m_attack_type_reduction[FIRE] = -75;
	g_attributes[MECHANICAL]->m_attack_type_reduction[PLASMA] = -30;
	g_attributes[MECHANICAL]->m_attack_type_reduction[LIGHT] = -10;
	g_attributes[MECHANICAL]->m_attack_type_reduction[ENERGY] = -10;
	g_attributes[MECHANICAL]->m_attack_type_reduction[WAVE] = -10;
	g_attributes[MECHANICAL]->m_attack_type_reduction[MIND] = 100;

	g_attributes[AERIAL] = new Attribute("Aerial", 50, 0, 0);
	g_attributes[AERIAL]->set(0, 5, 3, 0, 0, 0, 0, 0, 0, 0);

	g_attributes[SHARPSHOOTER] = new Attribute("Sharpshooter", 0, 50, 0);
	g_attributes[SHARPSHOOTER]->set(0, 0, 3, 5, 0, 0, 0, 0, 0, 0);

	g_attributes[LETHAL] = new Attribute("Lethal", 0, 0, 50);
	g_attributes[LETHAL]->set(0, 0, 0, 5, 3, 0, 0, 0, 0, 0);

	g_attributes[FIRE_MAGE] = new Attribute("Fire Mage", 0, 0, 0);
	g_attributes[FIRE_MAGE]->m_attack_type_bonus[FIRE] = 100;

	g_attributes[WIND_MAGE] = new Attribute("Wind Mage", 0, 0, 0);
	g_attributes[WIND_MAGE]->m_attack_type_bonus[WAVE] = 100;

	g_attributes[BLOOD_MAGE] = new Attribute("Blood Mage", 0, 0, 0);
	g_attributes[BLOOD_MAGE]->m_attack_type_bonus[BLOOD] = 100;

	g_attributes[DEATH_MAGE] = new Attribute("Death Mage", 0, 0, 0);
	g_attributes[DEATH_MAGE]->m_attack_type_bonus[DEATH] = 100;

	g_attributes[TIME_MAGE] = new Attribute("Time Mage", 0, 0, 0);
	g_attributes[TIME_MAGE]->m_attack_type_bonus[TIME] = 100;

	g_attributes[INADEPT] = new Attribute("Inadept", -50, -50, -50);
	g_attributes[INADEPT]->set(-5, -5, -5, -5, -5, -5, -5, -5, -5, -5);

	g_attributes[INEXPERIENCED] = new Attribute("Inexperienced", -35, -35, -35);
	g_attributes[INEXPERIENCED]->set(-3, -3, -3, -3, -3, -3, -3, -3, -3, -3);

	g_attributes[UNTRAINED] = new Attribute("Untrained", -25, -25, -25);
	g_attributes[UNTRAINED]->set(-2, -2, -2, -2, -2, -2, -2, -2, -2, -2);

	g_attributes[NOVICE] = new Attribute("Novice", -10, -10, -10);
	g_attributes[NOVICE]->set(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1);

	g_attributes[TRAINED] = new Attribute("Trained", 10, 10, 10);
	g_attributes[TRAINED]->set(1, 1, 1, 1, 1, 1, 1, 1, 1, 1);

	g_attributes[EXPERIENCED] = new Attribute("Experienced", 20, 20, 20);
	g_attributes[EXPERIENCED]->set(2, 2, 2, 2, 2, 2, 2, 2, 2, 2);

	g_attributes[EXPERT] = new Attribute("Expert", 30, 30, 30);
	g_attributes[EXPERT]->set(3, 3, 3, 3, 3, 3, 3, 3, 3, 3);

	g_attributes[VETERAN] = new Attribute("Veteran", 40, 40, 40);
	g_attributes[VETERAN]->set(4, 4, 4, 4, 4, 4, 4, 4, 4, 4);

	g_attributes[MASTER] = new Attribute("Master", 50, 50, 50);
	g_attributes[MASTER]->set(5, 5, 5, 5, 5, 5, 5, 5, 5, 5);

	g_attributes[LEGENDARY] = new Attribute("Legendary", 100, 100, 100);
	g_attributes[LEGENDARY]->set(10, 10, 10, 10, 10, 10, 10, 10, 10, 10);

	g_attributes[ARMORED_BLUNT] = new Attribute("Armored Blunt", 0, 0, 0);
	g_attributes[ARMORED_BLUNT]->m_attack_type_reduction[BLUNT] = 50;

	g_attributes[ARMORED_CUTTING] = new Attribute("Armored Cutting", 0, 0, 0);
	g_attributes[ARMORED_CUTTING]->m_attack_type_reduction[CUTTING] = 50;

	g_attributes[ARMORED_PIERCING] = new Attribute("Armored Piercing", 0, 0, 0);
	g_attributes[ARMORED_PIERCING]->m_attack_type_reduction[PIERCING] = 50;

	g_attributes[ARMORED_POISON] = new Attribute("Armored Poison", 0, 0, 0);
	g_attributes[ARMORED_POISON]->m_attack_type_reduction[POISON] = 50;

	g_attributes[ARMORED_LIGHT] = new Attribute("Armored Light", 0, 0, 0);
	g_attributes[ARMORED_LIGHT]->m_attack_type_reduction[LIGHT] = 50;

	g_attributes[ARMORED_HEAT] = new Attribute("Armored Heat", 0, 0, 0);
	g_attributes[ARMORED_HEAT]->m_attack_type_reduction[HEAT] = 50;

	g_attributes[ARMORED_COLD] = new Attribute("Armored Cold", 0, 0, 0);
	g_attributes[ARMORED_COLD]->m_attack_type_reduction[COLD] = 50;

	g_attributes[ARMORED_ELECTRIC] = new Attribute("Armored Electric", 0, 0, 0);
	g_attributes[ARMORED_ELECTRIC]->m_attack_type_reduction[ELECTRIC] = 50;

	g_attributes[ARMORED_ENERGY] = new Attribute("Armored Energy", 0, 0, 0);
	g_attributes[ARMORED_ENERGY]->m_attack_type_reduction[ENERGY] = 50;

	g_attributes[ARMORED_WAVE] = new Attribute("Armored Wave", 0, 0, 0);
	g_attributes[ARMORED_WAVE]->m_attack_type_reduction[WAVE] = 50;

	g_attributes[ARMORED_PLASMA] = new Attribute("Armored Plasma", 0, 0, 0);
	g_attributes[ARMORED_PLASMA]->m_attack_type_reduction[PLASMA] = 50;

	g_attributes[ARMORED_MIND] = new Attribute("Armored Mind", 0, 0, 0);
	g_attributes[ARMORED_MIND]->m_attack_type_reduction[MIND] = 50;

	g_attributes[ARMORED_TIME] = new Attribute("Armored Time", 0, 0, 0);
	g_attributes[ARMORED_TIME]->m_attack_type_reduction[TIME] = 50;

	g_attributes[ARMORED_SPACE] = new Attribute("Armored Space", 0, 0, 0);
	g_attributes[ARMORED_SPACE]->m_attack_type_reduction[SPACE] = 50;

	g_attributes[ARMORED_BLOOD] = new Attribute("Armored Blood", 0, 0, 0);
	g_attributes[ARMORED_BLOOD]->m_attack_type_reduction[BLOOD] = 50;

	g_attributes[ARMORED_DEATH] = new Attribute("Armored Death", 0, 0, 0);
	g_attributes[ARMORED_DEATH]->m_attack_type_reduction[DEATH] = 50;

	g_attributes[ARMORED_ACID] = new Attribute("Armored Acid", 0, 0, 0);
	g_attributes[ARMORED_ACID]->m_attack_type_reduction[ACID] = 50;

	g_attributes[ARMORED_COMBUSTION] = new Attribute("Armored Combustion", 0, 0, 0);
	g_attributes[ARMORED_COMBUSTION]->m_attack_type_reduction[COMBUSTION] = 50;

	g_attributes[IMMUNE_BLUNT] = new Attribute("Immune Blunt", 0, 0, 0);
	g_attributes[IMMUNE_BLUNT]->m_attack_type_reduction[BLUNT] = 100;

	g_attributes[IMMUNE_CUTTING] = new Attribute("Immune Cutting", 0, 0, 0);
	g_attributes[IMMUNE_CUTTING]->m_attack_type_reduction[CUTTING] = 100;

	g_attributes[IMMUNE_PIERCING] = new Attribute("Immune Piercing", 0, 0, 0);
	g_attributes[IMMUNE_PIERCING]->m_attack_type_reduction[PIERCING] = 100;

	g_attributes[IMMUNE_POISON] = new Attribute("Immune Poison", 0, 0, 0);
	g_attributes[IMMUNE_POISON]->m_attack_type_reduction[POISON] = 100;

	g_attributes[IMMUNE_LIGHT] = new Attribute("Immune Light", 0, 0, 0);
	g_attributes[IMMUNE_LIGHT]->m_attack_type_reduction[LIGHT] = 100;

	g_attributes[IMMUNE_HEAT] = new Attribute("Immune Heat", 0, 0, 0);
	g_attributes[IMMUNE_HEAT]->m_attack_type_reduction[HEAT] = 100;

	g_attributes[IMMUNE_COLD] = new Attribute("Immune Cold", 0, 0, 0);
	g_attributes[IMMUNE_COLD]->m_attack_type_reduction[COLD] = 100;

	g_attributes[IMMUNE_ELECTRIC] = new Attribute("Immune Electric", 0, 0, 0);
	g_attributes[IMMUNE_ELECTRIC]->m_attack_type_reduction[ELECTRIC] = 100;

	g_attributes[IMMUNE_ENERGY] = new Attribute("Immune Energy", 0, 0, 0);
	g_attributes[IMMUNE_ENERGY]->m_attack_type_reduction[ENERGY] = 100;

	g_attributes[IMMUNE_WAVE] = new Attribute("Immune Wave", 0, 0, 0);
	g_attributes[IMMUNE_WAVE]->m_attack_type_reduction[WAVE] = 100;

	g_attributes[IMMUNE_PLASMA] = new Attribute("Immune Plasma", 0, 0, 0);
	g_attributes[IMMUNE_PLASMA]->m_attack_type_reduction[PLASMA] = 100;

	g_attributes[IMMUNE_MIND] = new Attribute("Immune Mind", 0, 0, 0);
	g_attributes[IMMUNE_MIND]->m_attack_type_reduction[MIND] = 100;

	g_attributes[IMMUNE_TIME] = new Attribute("Immune Time", 0, 0, 0);
	g_attributes[IMMUNE_TIME]->m_attack_type_reduction[TIME] = 100;

	g_attributes[IMMUNE_SPACE] = new Attribute("Immune Space", 0, 0, 0);
	g_attributes[IMMUNE_SPACE]->m_attack_type_reduction[SPACE] = 100;

	g_attributes[IMMUNE_BLOOD] = new Attribute("Immune Blood", 0, 0, 0);
	g_attributes[IMMUNE_BLOOD]->m_attack_type_reduction[BLOOD] = 100;

	g_attributes[IMMUNE_DEATH] = new Attribute("Immune Death", 0, 0, 0);
	g_attributes[IMMUNE_DEATH]->m_attack_type_reduction[DEATH] = 100;

	g_attributes[IMMUNE_ACID] = new Attribute("Immune Acid", 0, 0, 0);
	g_attributes[IMMUNE_ACID]->m_attack_type_reduction[ACID] = 100;

	g_attributes[IMMUNE_COMBUSTION] = new Attribute("Immune Combustion", 0, 0, 0);
	g_attributes[IMMUNE_COMBUSTION]->m_attack_type_reduction[COMBUSTION] = 100;

	g_attributes[UNARMORED_BLUNT] = new Attribute("Unarmored Blunt", 0, 0, 0);
	g_attributes[UNARMORED_BLUNT]->m_attack_type_reduction[BLUNT] = -50;

	g_attributes[UNARMORED_CUTTING] = new Attribute("Unarmored Cutting", 0, 0, 0);
	g_attributes[UNARMORED_CUTTING]->m_attack_type_reduction[CUTTING] = -50;

	g_attributes[UNARMORED_PIERCING] = new Attribute("Unarmored Piercing", 0, 0, 0);
	g_attributes[UNARMORED_PIERCING]->m_attack_type_reduction[PIERCING] = -50;

	g_attributes[UNARMORED_POISON] = new Attribute("Unarmored Poison", 0, 0, 0);
	g_attributes[UNARMORED_POISON]->m_attack_type_reduction[POISON] = -50;

	g_attributes[UNARMORED_LIGHT] = new Attribute("Unarmored Light", 0, 0, 0);
	g_attributes[UNARMORED_LIGHT]->m_attack_type_reduction[LIGHT] = -50;

	g_attributes[UNARMORED_HEAT] = new Attribute("Unarmored Heat", 0, 0, 0);
	g_attributes[UNARMORED_HEAT]->m_attack_type_reduction[HEAT] = -50;

	g_attributes[UNARMORED_COLD] = new Attribute("Unarmored Cold", 0, 0, 0);
	g_attributes[UNARMORED_COLD]->m_attack_type_reduction[COLD] = -50;

	g_attributes[UNARMORED_ELECTRIC] = new Attribute("Unarmored Electric", 0, 0, 0);
	g_attributes[UNARMORED_ELECTRIC]->m_attack_type_reduction[ELECTRIC] = -50;

	g_attributes[UNARMORED_ENERGY] = new Attribute("Unarmored Energy", 0, 0, 0);
	g_attributes[UNARMORED_ENERGY]->m_attack_type_reduction[ENERGY] = -50;

	g_attributes[UNARMORED_WAVE] = new Attribute("Unarmored Wave", 0, 0, 0);
	g_attributes[UNARMORED_WAVE]->m_attack_type_reduction[WAVE] = -50;

	g_attributes[UNARMORED_PLASMA] = new Attribute("Unarmored Plasma", 0, 0, 0);
	g_attributes[UNARMORED_PLASMA]->m_attack_type_reduction[PLASMA] = -50;

	g_attributes[UNARMORED_MIND] = new Attribute("Unarmored Mind", 0, 0, 0);
	g_attributes[UNARMORED_MIND]->m_attack_type_reduction[MIND] = -50;

	g_attributes[UNARMORED_TIME] = new Attribute("Unarmored Time", 0, 0, 0);
	g_attributes[UNARMORED_TIME]->m_attack_type_reduction[TIME] = -50;

	g_attributes[UNARMORED_SPACE] = new Attribute("Unarmored Space", 0, 0, 0);
	g_attributes[UNARMORED_SPACE]->m_attack_type_reduction[SPACE] = -50;

	g_attributes[UNARMORED_BLOOD] = new Attribute("Unarmored Blood", 0, 0, 0);
	g_attributes[UNARMORED_BLOOD]->m_attack_type_reduction[BLOOD] = -50;

	g_attributes[UNARMORED_DEATH] = new Attribute("Unarmored Death", 0, 0, 0);
	g_attributes[UNARMORED_DEATH]->m_attack_type_reduction[DEATH] = -50;

	g_attributes[UNARMORED_ACID] = new Attribute("Unarmored Acid", 0, 0, 0);
	g_attributes[UNARMORED_ACID]->m_attack_type_reduction[ACID] = -50;

	g_attributes[UNARMORED_COMBUSTION] = new Attribute("Unarmored Combustion", 0, 0, 0);
	g_attributes[UNARMORED_COMBUSTION]->m_attack_type_reduction[COMBUSTION] = -50;

	g_attributes[DEADLY_BLUNT] = new Attribute("Deadly Blunt", 0, 0, 0);
	g_attributes[DEADLY_BLUNT]->m_attack_type_reduction[BLUNT] = -100;

	g_attributes[DEADLY_CUTTING] = new Attribute("Deadly Cutting", 0, 0, 0);
	g_attributes[DEADLY_CUTTING]->m_attack_type_reduction[CUTTING] = -100;

	g_attributes[DEADLY_PIERCING] = new Attribute("Deadly Piercing", 0, 0, 0);
	g_attributes[DEADLY_PIERCING]->m_attack_type_reduction[PIERCING] = -100;

	g_attributes[DEADLY_POISON] = new Attribute("Deadly Poison", 0, 0, 0);
	g_attributes[DEADLY_POISON]->m_attack_type_reduction[POISON] = -100;

	g_attributes[DEADLY_LIGHT] = new Attribute("Deadly Light", 0, 0, 0);
	g_attributes[DEADLY_LIGHT]->m_attack_type_reduction[LIGHT] = -100;

	g_attributes[DEADLY_HEAT] = new Attribute("Deadly Heat", 0, 0, 0);
	g_attributes[DEADLY_HEAT]->m_attack_type_reduction[HEAT] = -100;

	g_attributes[DEADLY_COLD] = new Attribute("Deadly Cold", 0, 0, 0);
	g_attributes[DEADLY_COLD]->m_attack_type_reduction[COLD] = -100;

	g_attributes[DEADLY_ELECTRIC] = new Attribute("Deadly Electric", 0, 0, 0);
	g_attributes[DEADLY_ELECTRIC]->m_attack_type_reduction[ELECTRIC] = -100;

	g_attributes[DEADLY_ENERGY] = new Attribute("Deadly Energy", 0, 0, 0);
	g_attributes[DEADLY_ENERGY]->m_attack_type_reduction[ENERGY] = -100;

	g_attributes[DEADLY_WAVE] = new Attribute("Deadly Wave", 0, 0, 0);
	g_attributes[DEADLY_WAVE]->m_attack_type_reduction[WAVE] = -100;

	g_attributes[DEADLY_PLASMA] = new Attribute("Deadly Plasma", 0, 0, 0);
	g_attributes[DEADLY_PLASMA]->m_attack_type_reduction[PLASMA] = -100;

	g_attributes[DEADLY_MIND] = new Attribute("Deadly Mind", 0, 0, 0);
	g_attributes[DEADLY_MIND]->m_attack_type_reduction[MIND] = -100;

	g_attributes[DEADLY_TIME] = new Attribute("Deadly Time", 0, 0, 0);
	g_attributes[DEADLY_TIME]->m_attack_type_reduction[TIME] = -100;

	g_attributes[DEADLY_SPACE] = new Attribute("Deadly Space", 0, 0, 0);
	g_attributes[DEADLY_SPACE]->m_attack_type_reduction[SPACE] = -100;

	g_attributes[DEADLY_BLOOD] = new Attribute("Deadly Blood", 0, 0, 0);
	g_attributes[DEADLY_BLOOD]->m_attack_type_reduction[BLOOD] = -100;

	g_attributes[DEADLY_DEATH] = new Attribute("Deadly Death", 0, 0, 0);
	g_attributes[DEADLY_DEATH]->m_attack_type_reduction[DEATH] = -100;

	g_attributes[DEADLY_ACID] = new Attribute("Deadly Acid", 0, 0, 0);
	g_attributes[DEADLY_ACID]->m_attack_type_reduction[ACID] = -100;

	g_attributes[DEADLY_COMBUSTION] = new Attribute("Deadly Combustion", 0, 0, 0);
	g_attributes[DEADLY_COMBUSTION]->m_attack_type_reduction[COMBUSTION] = -100;

	g_attributes[ENHANCED_STRENGTH] = new Attribute("Enhanced Strength", 0, 0, 0);
	g_attributes[ENHANCED_STRENGTH]->set(0, 0, 0, 0, 10, 0, 0, 0, 0, 0);
}