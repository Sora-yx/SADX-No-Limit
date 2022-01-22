#include "pch.h"
#include "startpos.h"

Trampoline* SetNextLevel_t = nullptr;

void StartPosLevel() {

	for (int i = 0; i < LengthOfArray(New_StartPosSonic); i++)
		HelperFunctionsGlobal.RegisterStartPosition(Characters_Sonic, New_StartPosSonic[i]);

	for (int i = 0; i < LengthOfArray(New_StartPosMiles); i++) 
		HelperFunctionsGlobal.RegisterStartPosition(Characters_Tails, New_StartPosMiles[i]);

	for (int i = 0; i < LengthOfArray(New_StartPosKnux); i++)
		HelperFunctionsGlobal.RegisterStartPosition(Characters_Knuckles, New_StartPosKnux[i]);

	for (int i = 0; i < LengthOfArray(New_StartPosAmy); i++)
		HelperFunctionsGlobal.RegisterStartPosition(Characters_Amy, New_StartPosAmy[i]);

	for (int i = 0; i < LengthOfArray(New_StartPosGamma); i++)
		HelperFunctionsGlobal.RegisterStartPosition(Characters_Gamma, New_StartPosGamma[i]);

	for (int i = 0; i < LengthOfArray(New_StartPosBig); i++) 
		HelperFunctionsGlobal.RegisterStartPosition(Characters_Big, New_StartPosBig[i]);

	return;
}


void __cdecl SetNextLevel_r(unsigned __int16 level)
{
	if (!IsAdventureComplete(SelectedCharacter) || level == LevelIDs_TwinkleCircuit || level >= LevelIDs_Chaos0 && level != LevelIDs_SandHill)
	{
		WriteData((short*)0x414b2e, CurrentCharacter);
		FunctionPointer(void, original, (unsigned __int16 level), SetNextLevel_t->Target());
		return original(level);
	}

	short curCharacter = Characters_Sonic;

	WriteData((short*)0x414b2e, curCharacter);

	if (CurrentLevel == LevelIDs_HotShelter)
		curCharacter = Characters_Amy;

	if (CurrentLevel == LevelIDs_SkyDeck && CurrentCharacter == Characters_Knuckles)
		curCharacter = Characters_Knuckles;
	
	FunctionPointer(void, original, (unsigned __int16 level), SetNextLevel_t->Target());
	return original(level);
}

void init_StartPosHack() {

	if (ChangeStartPos)
		StartPosLevel();

	//teleport player at the correct place when finishing a non intended stage, fix save corruption and wrong warp.
	SetNextLevel_t = new Trampoline((int)SetNextLevel, (int)SetNextLevel + 0x6, SetNextLevel_r);
	return;
}