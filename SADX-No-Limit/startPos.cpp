#include "pch.h"
#include "startpos.h"

Trampoline* SetNextLevel_t = nullptr;
short curCharacter_r = 0;

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

//used to fix destination when completing a stage with a non intended character.
void __cdecl SetNextLevel_r(unsigned __int16 level)
{
	curCharacter_r = CurrentCharacter;

	if (!IsAdventureComplete(CurrentCharacter) || level == LevelIDs_TwinkleCircuit || level >= LevelIDs_Chaos0 && level != LevelIDs_SandHill)
	{
		FunctionPointer(void, original, (unsigned __int16 level), SetNextLevel_t->Target());
		return original(level);
	}

	if (CurrentLevel == LevelIDs_HotShelter)
		curCharacter_r = Characters_Amy;

	if (CurrentLevel == LevelIDs_SkyDeck && CurrentCharacter == Characters_Knuckles)
		curCharacter_r = Characters_Knuckles;
	
	FunctionPointer(void, original, (unsigned __int16 level), SetNextLevel_t->Target());
	return original(level);
}

void init_StartPosHack() {

	if (ChangeStartPos)
		StartPosLevel();

	//teleport player at the correct place when finishing a non intended stage, fix save corruption and wrong warp.
	SetNextLevel_t = new Trampoline((int)SetNextLevel, (int)SetNextLevel + 0x6, SetNextLevel_r);
	WriteData((short**)0x414b2e, &curCharacter_r); //change the character variable used to teleport the player to the next level
	return;
}