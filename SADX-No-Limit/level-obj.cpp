#include "pch.h"

Trampoline* Balloon_Load_T = nullptr;
Trampoline* OGate2_Main_t = nullptr;

void __cdecl CheckLoadBalloon_r(ObjectMaster* a1) {

	if (CurrentCharacter != Characters_Amy)
	{
		a1->Data1->Position.y -= 38;
		return Capsule_Load(a1);
	}

	ObjectFunc(origin, Balloon_Load_T->Target());
	origin(a1);

}

void FixRollerCoaster() {

	if (EntityData1Ptrs[0])
		EntityData1Ptrs[0]->Action = 28; //force the character to leave the RC
}

void FixRCCharacterAction() {
	if (!CharObj2Ptrs[0])
		return;

	ForcePlayerAction(0, 18);

	PlaySound(0x4d, 0, 0, 0);
	return;
}

void __cdecl Start_TailsCutscene(__int16 a1)
{
	if (IsAdventureComplete(SelectedCharacter) && CurrentCharacter == Characters_Tails)
	{
		return;
	}

	return StartLevelCutscene(a1);
}

void __cdecl SetLevelClear_r(Uint32 level)
{
	//if the stage isn't a regular stage for the character, don't mark it as complete to avoid save corruption

	for (uint8_t i = 0; i < TrialLevels[SelectedCharacter].Count; i++)
	{
		if (TrialLevels[SelectedCharacter].Levels[i].Level == CurrentLevel && TrialLevels[SelectedCharacter].Levels[i].Act == CurrentAct)
		{
			return SetLevelClear(level); //call original function
		}
	}

	return;
}

void FixFlipperCharacterPosition() {

	if (CurrentLevel == LevelIDs_Casinopolis && CurrentAct > 1)
	{
		if (CurrentCharacter == Characters_Sonic)
			ForcePlayerAction(0, 0x2d);
		else
			ForcePlayerAction(0, 24);
	}

}

void FixInvisibleWall() {

	//if Sonic layout, add an invisible wall, if not, return.
	if (CurrentCharacter != Characters_Knuckles)
		LoadObject((LoadObj)2, 6, InvisibleWallCasino);

	return;
}

void Fix_PlayerPositionInPinball(Uint8 charIndex, float x, float y, float z) {

	if (CurrentCharacter >= Characters_Gamma) {
		x = 0;
		y = 192.295;
		z = 51.5;
	}

	return PositionPlayer(charIndex, x, y, z);
}

void __cdecl OGate2_Main_r(ObjectMaster* obj)
{
	EntityData1* data = obj->Data1;

	if (CurrentCharacter != Characters_Amy && data->Action < 2)
		obj->Data1->Action = 2;

	ObjectFunc(origin, OGate2_Main_t->Target());
	origin(obj);
}


void init_LevelObjectsHack() {

	//Twinkle Park
	WriteData<5>((int*)0x61cb77, 0x90); //Fix Twinkle Park Act 2 crash when not Sonic-Amy-Big
	WriteData<1>((char*)0x61cf97, 0x08); //Allow everyone to use Amy Twinkle Park transition part 1
	WriteData<1>((int*)0x61cf99, 0x84); //Allow everyone to use Amy Twinkle Park transition part 2
	WriteData<1>((int*)0x61dd72, 0x85); //Make Rollercoaster works when not Sonic.
	WriteCall((void*)0x61dd82, FixRCCharacterAction);
	WriteCall((void*)0x61dde8, FixRollerCoaster); //Fix leaving RC when not Sonic.

	//SH
	WriteData<6>((int*)0x61006a, 0x90); // Allow Speed Highway act 2 for every characters.

	WriteData<1>((char*)0x427FCA, 0x08); //Fix EC HUD display for Tails.

	//Prevent the game to start the cutscene as Tails.  
	WriteCall((void*)0x4F6B06, Start_TailsCutscene);
	WriteCall((void*)0x601570, GetCharacterID_r);


	//RM
	WriteData<5>((int*)0x6008b1, 0x90); //Fix Red Mountain Act 2 music as Tails.
	WriteData<5>((int*)0x601595, 0x90); //Remove player check when you enter at Red Mountain act 2.

	//Cas
	WriteData<2>((int*)0x5d049e, 0x90); //Add Invisible wall when not Sonic. (drop ring Emerald room.)
	WriteCall((void*)0x5d04a9, FixInvisibleWall); //Add invisible wall if sonic version, otherwise remove it.    
	WriteCall((void*)0x5dacc8, FixFlipperCharacterPosition);
	WriteCall((void*)0x5d6914, FixFlipperCharacterPosition);
	WriteCall((void*)0x5d6997, FixFlipperCharacterPosition);
	WriteCall((void*)0x5da671, FixFlipperCharacterPosition);
	WriteCall((void*)0x5C0812, Fix_PlayerPositionInPinball);
	WriteCall((void*)0x5C0E77, Fix_PlayerPositionInPinball);

	//security to avoid potential save file corruption
	WriteCall((void*)0x415066, SetLevelClear_r);
	WriteCall((void*)0x416D98, SetLevelClear_r);


	Balloon_Load_T = new Trampoline((int)Balloon_Main, (int)Balloon_Main + 0x6, CheckLoadBalloon_r);
	OGate2_Main_t = new Trampoline(0x59C850, 0x59C858, OGate2_Main_r);

	return;

}
