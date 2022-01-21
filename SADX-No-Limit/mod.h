#pragma once

#define MaxPlayers 8
extern HelperFunctions HelperFunctionsGlobal;


void ReadConfig(const char* path, const HelperFunctions& helperFunctions);
void init_StartPosHack();
void init_HubObjectsHack();
void init_LevelObjectsHack();