#include "pch.h"
#include "startpos.h"

Trampoline* SetNextLevel_t = nullptr;
short curCharacter_r = 0;
extern bool level[13];

bool isLevelBanned(char lvl)
{
	if (lvl < 13 && level[lvl] == false)
	{
		return true;
	}

	return false;
}

void StartPosLevel() {

	for (int i = 0; i < LengthOfArray(New_StartPosSonic); i++)
	{
		char lvl = New_StartPosSonic[i].LevelID;

		if (isLevelBanned(lvl))
		{
			continue;
		}
		
		HelperFunctionsGlobal.RegisterStartPosition(Characters_Sonic, New_StartPosSonic[i]);
	}

	for (int i = 0; i < LengthOfArray(New_StartPosMiles); i++)
	{
		char lvl1 = New_StartPosMiles[i].LevelID;

		if (isLevelBanned(lvl1))
		{
			continue;
		}

		HelperFunctionsGlobal.RegisterStartPosition(Characters_Tails, New_StartPosMiles[i]); 
	}

	for (int i = 0; i < LengthOfArray(New_StartPosKnux); i++)
	{
		char lvl2 = New_StartPosKnux[i].LevelID;

		if (isLevelBanned(lvl2))
		{
			continue;
		}
		HelperFunctionsGlobal.RegisterStartPosition(Characters_Knuckles, New_StartPosKnux[i]);
	}

	for (int i = 0; i < LengthOfArray(New_StartPosAmy); i++)
	{
		char lvl3 = New_StartPosAmy[i].LevelID;

		if (isLevelBanned(lvl3))
		{
			continue;
		}

		HelperFunctionsGlobal.RegisterStartPosition(Characters_Amy, New_StartPosAmy[i]);
	}

	for (int i = 0; i < LengthOfArray(New_StartPosGamma); i++)
	{
		char lvl4 = New_StartPosGamma[i].LevelID;

		if (isLevelBanned(lvl4))
		{
			continue;
		}

		HelperFunctionsGlobal.RegisterStartPosition(Characters_Gamma, New_StartPosGamma[i]);
	}

	for (int i = 0; i < LengthOfArray(New_StartPosBig); i++)
	{
		char lvl5 = New_StartPosBig[i].LevelID;

		if (isLevelBanned(lvl5))
		{
			continue;
		}

		HelperFunctionsGlobal.RegisterStartPosition(Characters_Big, New_StartPosBig[i]);
	}

	return;
}

//used to fix destination when completing a stage with a non intended character.
void __cdecl SetNextLevel_r(unsigned __int16 level)
{
	curCharacter_r = CurrentCharacter;

	if (!IsAdventureComplete(SelectedCharacter) || level == LevelIDs_TwinkleCircuit || level >= LevelIDs_Chaos0 && level != LevelIDs_SandHill)
	{
		FunctionPointer(void, original, (unsigned __int16 level), SetNextLevel_t->Target());
		return original(level);
	}

	curCharacter_r = Characters_Sonic;

	if (CurrentLevel == LevelIDs_HotShelter)
		curCharacter_r = Characters_Amy;

	if (CurrentLevel == LevelIDs_SkyDeck && CurrentCharacter == Characters_Knuckles)
		curCharacter_r = Characters_Knuckles;
	
	FunctionPointer(void, original, (unsigned __int16 level), SetNextLevel_t->Target());
	return original(level);
}

void init_StartPosHack() {


	StartPosLevel();

	//teleport player at the correct place when finishing a non intended stage, fix save corruption and wrong warp.
	SetNextLevel_t = new Trampoline((int)SetNextLevel, (int)SetNextLevel + 0x6, SetNextLevel_r);
	WriteData((short**)0x414b2e, &curCharacter_r); //change the character variable used to teleport the player to the next level
	return;
}