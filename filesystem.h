#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <fstream>
#include "defs.h"

enum
{
	INPUT,
	OUTPUT
};

enum
{
	NAME_STORE,
	NICKNAME_STORE,
	STAT_STORE,
	STAT_CHANCES_STORE,
	LEVEL_STORE,
	REQ_STORE,
	HEAL_STORE,
	ORGANIC_STORE,
	POWER_START_STORE,
	POWER_END_STORE,
	MOVE_STORE,
	USES_STORE,
	LIMS_STORE,
	PROFICIENCIES_STORE,
	GENDER_STORE,
	EYE_STORE,
	HAIR_STORE,
	ORIGIN_STORE,
	MARTIAL_STATUS_STORE,
	FEET_STORE,
	INCHES_STORE,
	WEIGHT_STORE,
	AGE_STORE,
	YEAR_STORE,
	MONTH_STORE,
	DAY_STORE,
	MONTH_STR_STORE,
	BIRTH_PLACE_STORE,
	DESCRIPTION_START_STORE,
	END_STORE
};

struct heroSaveData
{
	std::string m_name;
	std::string m_nickname;
	int m_stats[NUM_STATS] = {};
	int m_stat_chances[NUM_STATS] = {};
	int m_level;
	int m_level_req;
	int m_can_heal_from_damage;
	int m_is_organic;

	std::vector<int> m_powers_id;

	int m_moves_id[MAX_MOVES];
	int m_uses[MAX_MOVES];
	int m_lims[MAX_MOVES];
	int m_proficiencies[MAX_MOVES];

	int m_is_female;
	int m_eye_id;
	int m_hair_id;
	int m_origin_id;
	int m_martial_status;
	int m_feet;
	int m_inches;
	int m_weight;
	int m_age;
	int m_year;
	int m_month;
	int m_day;

	std::string m_month_str;
	std::string m_birth_place;
	std::string m_description_str;
};

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	void writeBattleString(const std::string str);
	void writeHeroData(const std::string filename, heroSaveData& data, const int dir);
	heroSaveData* parseHeroData(const std::string filename, const int dir, const bool debug = false);
	const std::string listDirContents(const int dir, const std::string extension = ".dsf");
	std::string promptFilename(const std::string question);

	static FileSystem* get()
	{
		static FileSystem* fs = new FileSystem();
		return fs;
	}
private:
	const std::string m_battles_dir = "saved_battles/";
	const std::string m_base_dir = "base/";
	const std::string m_saves_dir = "saves/";
	const std::string m_custom_dir = "custom/";
	const std::string m_extension = ".dsf";

	std::string m_output_file_name = "";
	std::string m_input_file_name = "";

	std::ifstream m_input_file;
	std::ofstream m_output_file;

	heroSaveData m_last_saved_data;

	void openFile(const std::string name, const int file_type);
	void closeFile(const int file_type);
	void writeLine(const std::string line);
	void writeIntLine(const int line);
	std::string readLine(const bool debug = false);
	int readIntLine(const bool debug = false);
	std::string getDirFromType(const int type);
};

#endif