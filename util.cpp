#include "util.h"

std::string getDamageTypeString(const int slot)
{
	switch(slot)
	{
		case PHYSICAL:
		{
			return "Physical";
		}
		case ENERGY_TYPE:
		{
			return "Energy";
		}
		case SPECIAL:
		{
			return "Mental";
		}
	}
}

std::string getStatString(const int slot)
{
	switch(slot)
	{
		case HEALTH:
		{
			return "Health"; 
		}
		case SPEED:
		{
			return "Speed";
		}
		case AGILITY:
		{
			return "Agility";
		}
		case SKILL:
		{
			return "Skill";
		}
		case P_STR:
		{
			return "Physical Strength";
		}
		case E_STR:
		{
			return "Energy Power";
		}
		case S_STR:
		{
			return "Mental Power";
		}
		case P_DUR:
		{
			return "Physical Durability";
		}
		case E_DUR:
		{
			return "Energy Resistance";
		}
		case S_DUR:
		{
			return "Mental Resistance";
		}
		case KNOW:
		{
			return "Knowlegde";
		}
		case SENSE:
		{
			return "Sensory";
		}
		case CHARM:
		{
			return "Charmisa";
		}
		case APPEAL:
		{
			return "Appeal";
		}
	}
}

std::string getShortenStatString(const int slot)
{
	switch(slot)
	{
		case HEALTH:
		{
			return "He"; 
		}
		case SPEED:
		{
			return "Sp";
		}
		case AGILITY:
		{
			return "Ag";
		}
		case SKILL:
		{
			return "Sk";
		}
		case P_STR:
		{
			return "P.S";
		}
		case E_STR:
		{
			return "E.P";
		}
		case S_STR:
		{
			return "M.P";
		}
		case P_DUR:
		{
			return "P.D";
		}
		case E_DUR:
		{
			return "E.R";
		}
		case S_DUR:
		{
			return "M.R";
		}
		case KNOW:
		{
			return "Kn";
		}
		case SENSE:
		{
			return "Se";
		}
		case CHARM:
		{
			return "Ch";
		}
		case APPEAL:
		{
			return "Ap";
		}
	}
}