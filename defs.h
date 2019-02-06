#ifndef DEFS_H
#define DEFS_H

#include <vector>
#include <stdint.h>
#include <string>
#include <iostream>
#include <stdexcept> 
#include <memory>

enum {PHYSICAL, ENERGY_TYPE, SPECIAL, NUM_TYPES};
enum {ORGANIC_TYPE, MECHANICAL_TYPE, BIO_MECHANICAL_TYPE};
enum {HEALTH, SPEED, AGILITY, SKILL, P_STR, E_STR, S_STR, P_DUR, E_DUR, S_DUR, KNOW, SENSE, CHARM, APPEAL, NUM_STATS};

enum
{
	BLUNT,
	CUTTING,
	PIERCING,
	POISON,
	LIGHT,
	HEAT,
	COLD,
	ELECTRIC,
	ENERGY,
	WAVE,
	PLASMA,
	MIND,
	TIME,
	SPACE,
	BLOOD,
	DEATH,
	ACID,
	COMBUSTION,
	NUM_ATTACK_TYPES
};

enum
{
	STUN,
	BLEED,
	AFFLICT,
	FIRE,
	FREEZE,
	DISORIENT,
	CURSE,
	NUM_STATUS_EFFECTS
};

enum
{
	ORGANIC,
	MECHANICAL,
	AERIAL,
	SHARPSHOOTER,
	LETHAL,
	FIRE_MAGE,
	DEATH_MAGE,
	BLOOD_MAGE,
	TIME_MAGE,
	WIND_MAGE,
	INADEPT,
	INEXPERIENCED,
	UNTRAINED,
	NOVICE,
	TRAINED,
	EXPERIENCED,
	EXPERT,
	VETERAN,
	MASTER,
	LEGENDARY,
	ARMORED_BLUNT,
	ARMORED_CUTTING,
	ARMORED_PIERCING,
	ARMORED_POISON,
	ARMORED_LIGHT,
	ARMORED_HEAT,
	ARMORED_COLD,
	ARMORED_ELECTRIC,
	ARMORED_ENERGY,
	ARMORED_WAVE,
	ARMORED_PLASMA,
	ARMORED_MIND,
	ARMORED_TIME,
	ARMORED_SPACE,
	ARMORED_BLOOD,
	ARMORED_DEATH,
	ARMORED_ACID,
	ARMORED_COMBUSTION,
	IMMUNE_BLUNT,
	IMMUNE_CUTTING,
	IMMUNE_PIERCING,
	IMMUNE_POISON,
	IMMUNE_LIGHT,
	IMMUNE_HEAT,
	IMMUNE_COLD,
	IMMUNE_ELECTRIC,
	IMMUNE_ENERGY,
	IMMUNE_WAVE,
	IMMUNE_PLASMA,
	IMMUNE_MIND,
	IMMUNE_TIME,
	IMMUNE_SPACE,
	IMMUNE_BLOOD,
	IMMUNE_DEATH,
	IMMUNE_ACID,
	IMMUNE_COMBUSTION,
	UNARMORED_BLUNT,
	UNARMORED_CUTTING,
	UNARMORED_PIERCING,
	UNARMORED_POISON,
	UNARMORED_LIGHT,
	UNARMORED_HEAT,
	UNARMORED_COLD,
	UNARMORED_ELECTRIC,
	UNARMORED_ENERGY,
	UNARMORED_WAVE,
	UNARMORED_PLASMA,
	UNARMORED_MIND,
	UNARMORED_TIME,
	UNARMORED_SPACE,
	UNARMORED_BLOOD,
	UNARMORED_DEATH,
	UNARMORED_ACID,
	UNARMORED_COMBUSTION,
	DEADLY_BLUNT,
	DEADLY_CUTTING,
	DEADLY_PIERCING,
	DEADLY_POISON,
	DEADLY_LIGHT,
	DEADLY_HEAT,
	DEADLY_COLD,
	DEADLY_ELECTRIC,
	DEADLY_ENERGY,
	DEADLY_WAVE,
	DEADLY_PLASMA,
	DEADLY_MIND,
	DEADLY_TIME,
	DEADLY_SPACE,
	DEADLY_BLOOD,
	DEADLY_DEATH,
	DEADLY_ACID,
	DEADLY_COMBUSTION,
	ENHANCED_STRENGTH,
	NUM_ATTRIBUTES
};

enum 
{
	PUNCH,
	KICK,
	POWER_PUNCH,
	THROW_ROCK,
	CHARGE,
	BLOCK,
	TENSE,
	BOLT_ACTION_SHOT,
	TAKE_AIM,
	SEMI_AUTO_SHOT,
	VOLLEY_SHOT,
	FULL_AUTO_SHOT,
	NUM_MOVES
};

enum
{
	//Renegades start
	LAMBERT, //Turkish-American - Supersoldier [VARIOUS WEAPONS]
	DARCY, //Irish - Psuedo-Goddess [ICKLENELLIEROSE] [RED HAIR] [FRECKLES]
	AGNES, //Elekton [ELECTROKINESIS] [PINKERFISH]
	THOMAS, //English - Mage
	NELLIE, //Norwegian - Force Field [JENNIE]
	HANA, //Native American - Telepathic
	GILL, //American - Necromancer
	CELICA, //Canadian - Demigoddess [BUGA] BLONDE [CYNTHIA - Pokemon]
	HANSO, //Chinese-American - Supersoldier [SWORD] 
	KYRA, //American - Plasma Generation DIRTY BLONDE [ANNA MAE RENEE]
	SUSANA, //Japanese - Invisibility, Flight, Intangibility [AKAME]
	EVELYN, //American - Space Shifting [Trans] RED HAIR [EVE]
	EILENA, //Australian - Plant Manipulation [Blue Hair] [CLAUDIA]
	BRODER, //Unknown - Giga Soldier [AUT]
	INIGO, //American - Arty
	TAKASHI, //Arty
	LEESA, //American Deviant - Eagle Wings [Flight] STRAWBERRY BLONDE [FAERY]
	AMELIA, //Mexican - Animal Manipulation  SHY  [ALICIA]
	SUZY, //American Super Soldier - [Sniper] DIRTY BLONDE [NOISYBUTTERS]
	MELANE, //Croatia - Conviction BLACK [BREEBUNN]
	LOREN,//Jewish Luxembourgish - Illision BROWN [HANNAH WITTON]
	SARA, //Jewish Canadian - Thermal Manipulation LIGHT BROWN [SARAH Z]
	EIDTH, //African - American Gold Touch
	//Young Kids [13 under]
	MAGGIE, //American [EXTREME STRENGTH and DURABILITY] 10 BLONDE [SAM]
	DANNY, //German American [Teleportation] 12
	MARK, //ARTY 8
	ETHAN, //Persian 12 [Wind Magic]
	JOHN, //ARTY 11 [EXTREME Accuracy]
	LINDSAY, //American 12 [TELEKINESIS] DIRTY BLONDE [Freckles]
	SUMMER, //Canadian 11 TECTONIC PLATE MANIPULATION [RED HAIR]
	NINA, //American Empathic Manipulation 12 [BLACK HAIR] [ISOLATED]
	YUI, //KOREAN American 9 Technology Manipulation
	GEORGIE, //English - American 10 [Brown Hair] Reanimation
};

enum 
{
	SUPER_STRENGTH,
	SUPER_REFLEXES,
	REGENERATION,
	SUPER_DURABILITY,
	ELECTRIC_IMMUNITY,
	SSRD_RIFLE_1,
	NUM_POWERS
};

enum
{
	MALE_INT,
	FEMALE_INT
};

enum
{
	MOVE_SLOT_1 = 0,
	MOVE_SLOT_2,
	MOVE_SLOT_3,
	MOVE_SLOT_4,
	MOVE_SLOT_5,
	MOVE_SLOT_6,
	MAX_MOVES
};

enum
{
	BATTLES_DIR,
	BASE_DIR,
	SAVES_DIR,
	CUSTOM_DIR
};

#endif