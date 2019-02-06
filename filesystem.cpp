#include "filesystem.h"
#include "console.h"

FileSystem::FileSystem()
{

}

FileSystem::~FileSystem()
{
	closeFile(INPUT);
	closeFile(OUTPUT);
}

void FileSystem::openFile(const std::string name, const int file_type)
{
	using namespace e_std;

	if(file_type == OUTPUT)
	{
		if(!m_output_file.is_open())
		{
			m_output_file_name = name;
			m_output_file.open(m_output_file_name);
		}
		else
		{
			println("Error! Output File still open! Currently Open File: "+m_output_file_name);
		}
	}
	else if(file_type == INPUT)
	{
		if(!m_input_file.is_open())
		{
			m_input_file_name = name;
			m_input_file = std::ifstream(m_input_file_name);

			if(!m_input_file.is_open())
			{
				println("Error! Able to open file: "+m_input_file_name);

				/*if(!m_output_file.is_open())
				{
					println("Attempting to create a new one...");
					openFile(m_input_file_name, OUTPUT);
				}*/
			}
		}
		else
		{
			println("Error! Input File still open! Currently Open File: "+m_input_file_name);
		}
	}
}

void FileSystem::closeFile(const int file_type)
{
	if(file_type == INPUT && m_input_file.is_open())
	{
		m_input_file.close();
	}
	else if(file_type == OUTPUT && m_output_file.is_open())
	{
		m_output_file.close();
	}
}

void FileSystem::writeIntLine(const int line)
{
	writeLine(std::to_string(line));
}

void FileSystem::writeLine(const std::string line)
{
	using namespace e_std;

	if(m_output_file.is_open())
	{
		m_output_file << line << "\n";
	}
	else
	{
		println("Error! Unable to write to file! Output File not open.");
	}
}

int FileSystem::readIntLine(const bool debug)
{
	return std::stoi(readLine(debug));
}

std::string FileSystem::readLine(const bool debug)
{
	using namespace e_std;
	std::string line;

	if(m_input_file.is_open())
	{
		if(getline(m_input_file, line))
		{
			if(debug) println("Read: " + line + "\nFrom file.");
		}
		else
		{
			println("Error! End of file reached for: " + m_input_file_name);
		}

	}
	else
	{
		println("Error! Unable to read from file! Input File not open.");
	}

	return line;
}

std::string FileSystem::getDirFromType(const int type)
{
	switch(type)
	{
		case BATTLES_DIR:
		{
			return m_battles_dir;
		}
		case BASE_DIR:
		{
			return m_base_dir;
		}
		case SAVES_DIR:
		{
			return m_saves_dir;
		}
		case CUSTOM_DIR:
		{
			return m_custom_dir;
		}
	}
}

void FileSystem::writeBattleString(const std::string str)
{
	std::string filename = m_battles_dir + promptFilename("What should the saved file be named?") + m_extension;
	openFile(filename, OUTPUT);
	writeLine(str);
	closeFile(OUTPUT);
}

void FileSystem::writeHeroData(const std::string filename, heroSaveData& data, const int dir)
{
	std::string name = getDirFromType(dir) + filename + m_extension;
	openFile(name, OUTPUT);
	
	writeIntLine(NAME_STORE);
	writeLine(data.m_name);
	writeIntLine(NICKNAME_STORE);
	writeLine(data.m_nickname);
	writeIntLine(STAT_STORE);

	for(int i = 0; i < NUM_STATS; i++)
	{
		writeIntLine(data.m_stats[i]);
	}

	writeIntLine(STAT_CHANCES_STORE);

	for(int i = 0; i < NUM_STATS; i++)
	{
		writeIntLine(data.m_stat_chances[i]);
	}

	writeIntLine(LEVEL_STORE);
	writeIntLine(data.m_level);
	writeIntLine(REQ_STORE);
	writeIntLine(data.m_level_req);
	writeIntLine(HEAL_STORE);
	writeIntLine(data.m_can_heal_from_damage);
	writeIntLine(ORGANIC_STORE);
	writeIntLine(data.m_is_organic);

	writeIntLine(POWER_START_STORE);

	for(auto p = data.m_powers_id.begin(); p != data.m_powers_id.end(); ++p)
	{
		writeIntLine(*p);
	}

	writeIntLine(POWER_END_STORE);
	writeIntLine(MOVE_STORE);

	for(int i = 0; i < MAX_MOVES; i++)
	{
		writeIntLine(data.m_moves_id[i]);
	}

	writeIntLine(USES_STORE);

	for(int i = 0; i < MAX_MOVES; i++)
	{
		writeIntLine(data.m_uses[i]);
	}

	writeIntLine(LIMS_STORE);

	for(int i = 0; i < MAX_MOVES; i++)
	{
		writeIntLine(data.m_lims[i]);
	}

	writeIntLine(PROFICIENCIES_STORE);

	for(int i = 0; i < NUM_STATS; i++)
	{
		writeIntLine(data.m_proficiencies[i]);
	}

	writeIntLine(GENDER_STORE);
	writeIntLine(data.m_is_female);
	writeIntLine(EYE_STORE);
	writeIntLine(data.m_eye_id);
	writeIntLine(HAIR_STORE);
	writeIntLine(data.m_hair_id);
	writeIntLine(ORIGIN_STORE);
	writeIntLine(data.m_origin_id);
	writeIntLine(MARTIAL_STATUS_STORE);
	writeIntLine(data.m_martial_status);
	writeIntLine(FEET_STORE);
	writeIntLine(data.m_feet);
	writeIntLine(INCHES_STORE);
	writeIntLine(data.m_inches);
	writeIntLine(WEIGHT_STORE);
	writeIntLine(data.m_weight);
	writeIntLine(AGE_STORE);
	writeIntLine(data.m_age);
	writeIntLine(YEAR_STORE);
	writeIntLine(data.m_year);
	writeIntLine(MONTH_STORE);
	writeIntLine(data.m_month);
	writeIntLine(DAY_STORE);
	writeIntLine(data.m_day);

	writeIntLine(MONTH_STR_STORE);
	writeLine(data.m_month_str);
	writeIntLine(BIRTH_PLACE_STORE);
	writeLine(data.m_birth_place);
	writeIntLine(DESCRIPTION_START_STORE);
	writeLine(data.m_description_str);

	writeIntLine(END_STORE);

	closeFile(OUTPUT);
}

heroSaveData* FileSystem::parseHeroData(const std::string filename, const int dir, const bool debug)
{
	std::string name = getDirFromType(dir) + filename + m_extension;
	static heroSaveData data = {};

	openFile(name, INPUT);

	bool reading_file = true;
	
	while(reading_file)
	{
		int bytecode = readIntLine(debug);
		switch(bytecode)
		{
			case NAME_STORE:
			{
				data.m_name = readLine(debug);
			}
			break;
			case NICKNAME_STORE:
			{
				data.m_nickname = readLine(debug);
			}
			break;
			case STAT_STORE:
			{
				for(int i = 0; i < NUM_STATS; i++)
				{
					data.m_stats[i] = readIntLine(debug);
				}
			}
			break;
			case STAT_CHANCES_STORE:
			{
				for(int i = 0; i < NUM_STATS; i++)
				{
					data.m_stat_chances[i] = readIntLine(debug);
				}
			}
			break;
			case LEVEL_STORE:
			{
				data.m_level = readIntLine(debug);
			}
			break;
			case REQ_STORE:
			{
				data.m_level_req = readIntLine(debug);
			}
			break;
			case HEAL_STORE:
			{
				data.m_can_heal_from_damage = readIntLine(debug);
			}
			break;
			case ORGANIC_STORE:
			{
				data.m_is_organic = readIntLine(debug);
			}
			break;
			case POWER_START_STORE:
			{
							//POWER_END_STORE
				int code = readIntLine(debug);

				while(code != POWER_END_STORE)
				{
					data.m_powers_id.push_back(code);
					code = readIntLine(debug);
				}
			}
			break;
			case MOVE_STORE:
			{
				for(int i = 0; i < MAX_MOVES; i++)
				{
					data.m_moves_id[i] = readIntLine(debug);
				}
			}
			break;
			case USES_STORE:
			{
				for(int i = 0; i < MAX_MOVES; i++)
				{
					data.m_uses[i] = readIntLine(debug);
				}
			}
			break;
			case LIMS_STORE:
			{
				for(int i = 0; i < MAX_MOVES; i++)
				{
					data.m_lims[i] = readIntLine(debug);
				}
			}
			break;
			case PROFICIENCIES_STORE:
			{
				for(int i = 0; i < NUM_STATS; i++)
				{
					data.m_proficiencies[i] = readIntLine(debug);
				}
			}
			break;
			case GENDER_STORE:
			{
				data.m_is_female = readIntLine(debug);
			}
			break;
			case EYE_STORE:
			{
				data.m_eye_id = readIntLine(debug);
			}
			break;
			case HAIR_STORE:
			{
				data.m_hair_id = readIntLine(debug);
			}
			break;
			case ORIGIN_STORE:
			{
				data.m_origin_id = readIntLine(debug);
			}
			break;
			case MARTIAL_STATUS_STORE:
			{
				data.m_martial_status = readIntLine(debug);
			}
			break;
			case FEET_STORE:
			{
				data.m_feet = readIntLine(debug);
			}
			break;
			case INCHES_STORE:
			{
				data.m_inches = readIntLine(debug);
			}
			break;
			case WEIGHT_STORE:
			{
				data.m_weight = readIntLine(debug);
			}
			break;
			case AGE_STORE:
			{
				data.m_age = readIntLine(debug);
			}
			break;
			case YEAR_STORE:
			{
				data.m_year = readIntLine(debug);
			}
			break;
			case MONTH_STORE:
			{
				data.m_month = readIntLine(debug);
			}
			break;
			case DAY_STORE:
			{
				data.m_day = readIntLine(debug);
			}
			break;
			case MONTH_STR_STORE:
			{
				data.m_month_str = readLine(debug);
			}
			break;
			case BIRTH_PLACE_STORE:
			{
				data.m_birth_place = readLine(debug);
			}
			break;
			case DESCRIPTION_START_STORE:
			{
				data.m_description_str = readLine(debug);
			}
			break;
			case END_STORE:
			{
				reading_file = false;
			}
			break;
		}
	}

	closeFile(INPUT);
	return &data;
}

//Todo later
const std::string FileSystem::listDirContents(const int dir, const std::string extension)
{
	//std::string dir = getDirFromType(dir);
	return "";
}

std::string FileSystem::promptFilename(const std::string question)
{
	std::string filename;

	e_std::loopAccept(question, "", &filename, STORE);

	return filename;
}
