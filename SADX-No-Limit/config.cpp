#include "pch.h"

bool level[13] = { true };

void ReadConfig(const char* path, const HelperFunctions& helperFunctions) {
	//Ini file Configuration
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
	level[1] = config->getBool("General", "EC", true);
	level[2] = config->getBool("General", "WV", true);
	level[3] = config->getBool("General", "TP", true);
	level[4] = config->getBool("General", "SH", true);
	level[5] = config->getBool("General", "RM", true);
	level[6] = config->getBool("General", "SD", true);
	level[7] = config->getBool("General", "LW", true);
	level[8] = config->getBool("General", "IC", true);
	level[9] = config->getBool("General", "CAS", true);
	level[10] = config->getBool("General", "FE", true);
	level[12] = config->getBool("General", "HS", true);


	delete config;

	return;
}