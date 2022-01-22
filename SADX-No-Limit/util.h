#pragma once


int __cdecl GetCharacterID_r(char index);
int __cdecl GetCurCharacter_r();
int __cdecl GetCharacterGamma_r(char index);
int __cdecl GetCharacterAmy_r(char index);
int __cdecl GetCharacterKnux_r(char index);
int __cdecl GetCurCharacterHS_r();
int __cdecl GetCharacterHotShelter_r(char index);
int __cdecl GetCharacterIDSkyDeck_r(char index);
int __cdecl GetCharacterSD_r();
int __cdecl GetCurCharKnux_r();
int __cdecl GetCurCharacterAmy_r();
int __cdecl GetCharacterMiles_r(char index);
int __cdecl GetCharIDTPDoor_r(char index);
int __cdecl GetCharacterBig_r(char index);

void TargetableEntity(ObjectMaster* obj);

void Remove_TargetCursor(ObjectMaster* obj);
void Check_AllocateObjectData2(ObjectMaster* obj, EntityData1* data1);