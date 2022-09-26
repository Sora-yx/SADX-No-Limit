#pragma once

#define MaxPlayers 8
extern HelperFunctions HelperFunctionsGlobal;
extern bool ChangeStartPos;


void ReadConfig(const char* path, const HelperFunctions& helperFunctions);
void init_StartPosHack();
void init_HubObjectsHack();
void init_LevelObjectsHack();

enum selectedCharE
{
	sonic,
	miles,
	knux,
	amy,
	big,
	gamma,
	ss
};