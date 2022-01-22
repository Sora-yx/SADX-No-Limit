#include "pch.h"

bool ChangeStartPos = false;

void ReadConfig(const char* path, const HelperFunctions& helperFunctions) {
	//Ini file Configuration
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
	ChangeStartPos = config->getBool("General", "ChangeStartPos", true);
	delete config;

	return;
}