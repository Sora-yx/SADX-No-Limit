#include "pch.h"

//trick the game to make a character able to access every areas

int __cdecl GetCharacterID_r(char index)
{
    if (IsAdventureComplete(CurrentCharacter))
    {
        return Characters_Sonic;
    }
    else {
        return GetCharacterID(index);
    }
}

int __cdecl GetCharacterMiles_r(char index)
{
    if (IsAdventureComplete(CurrentCharacter))
    {
        return Characters_Tails;
    }
    else {
        return GetCharacterID(index);
    }
}

int __cdecl GetCharacterKnux_r(char index)
{
    if (IsAdventureComplete(CurrentCharacter))
    {
        return Characters_Knuckles;
    }
    else {
        return GetCharacterID(index);
    }
}

int __cdecl GetCurCharKnux_r()
{
    if (IsAdventureComplete(CurrentCharacter))
    {
        return Characters_Knuckles;
    }
    else {
        return GetCurrentCharacterID();
    }
}

int __cdecl GetCharacterGamma_r(char index)
{
    if (IsAdventureComplete(CurrentCharacter))
    {
        return Characters_Gamma;
    }
    else {
        return GetCharacterID(index);
    }
}

int __cdecl GetCharacterAmy_r(char index)
{
    if (IsAdventureComplete(CurrentCharacter))
    {
        return Characters_Amy;
    }
    else {
        return GetCharacterID(index);
    }
}


int __cdecl GetCharacterBig_r(char index)
{
    if (IsAdventureComplete(CurrentCharacter))
    {
        return Characters_Big;
    }
    else {
        return GetCharacterID(index);
    }
}

int __cdecl GetCharacterHotShelter_r(char index)
{
    if (IsAdventureComplete(CurrentCharacter) && CurrentCharacter != Characters_Big && CurrentCharacter != Characters_Gamma)
    {
        return Characters_Amy;
    }
    else {
        return GetCharacterID(index);
    }
}

int __cdecl GetCurCharacterHS_r()
{
    if (IsAdventureComplete(CurrentCharacter) && CurrentCharacter != Characters_Big && CurrentCharacter != Characters_Gamma)
    {
        return Characters_Amy;
    }
    else {
        return GetCurrentCharacterID();

    }
}

int __cdecl GetCurCharRMMiles_r()
{
    if (CurrentCharacter == Characters_Tails && !IsAdventureComplete(CurrentCharacter))
    {
        return GetCurrentCharacterID();
    }

    return 8;
}

int __cdecl GetCharacterIDSkyDeck_r(char index)
{
    if (!IsAdventureComplete(CurrentCharacter))
        return GetCharacterID(index);

    if (CurrentAct == 5) //Sky Deck pool door check
        return Characters_Knuckles;

    if (CurrentCharacter != Characters_Tails)
    {
        return Characters_Sonic;
    }

    return GetCharacterID(index);
}

int __cdecl GetCharIDTPDoor_r(char index)
{
    if (!IsAdventureComplete(CurrentCharacter) || CurrentCharacter == Characters_Sonic || CurrentCharacter == Characters_Amy || CurrentCharacter == Characters_Big)
        return GetCharacterID(index);

    return Characters_Sonic;
}

int __cdecl GetCharacterSD_r()
{
    if (!IsAdventureComplete(CurrentCharacter) || CurrentCharacter == Characters_Knuckles)
        return GetCurrentCharacterID();

    if (CurrentAct == 5) //Sky Deck pool door check
        return Characters_Knuckles;

    if (CurrentCharacter != Characters_Tails)
    {
        return Characters_Sonic;
    }

    return GetCurrentCharacterID();
}


int __cdecl GetCurCharacterAmy_r()
{
    if (IsAdventureComplete(CurrentCharacter))
    {
        return Characters_Amy;
    }
    else {
        return GetCurrentCharacterID();

    }
}


int __cdecl GetCurCharacterBig_r()
{
    if (IsAdventureComplete(CurrentCharacter))
    {
        return Characters_Big;
    }
    else {
        return GetCurrentCharacterID();

    }
}

int __cdecl GetCurCharacter_r()
{
    if (IsAdventureComplete(CurrentCharacter))
    {
        return Characters_Sonic;
    }
    else {
        return GetCurrentCharacterID();

    }
}

//Create an object so Gamma can hit some specific bosses.
CollisionData col = { 0, 0, 0x77, 0, 0x800400,  { 6.0, 6.0, 6.0}, 0, 0 };

void TargetableEntity(ObjectMaster* obj)
{
    EntityData1* data = obj->Data1;

    if (data->Action == 0) {
        AllocateObjectData2(obj, obj->Data1);

        //if the scale is specified, temporary set the collision scale to it.
        if (data->Scale.x) {
            Collision_Init(obj, &col, 1, 2u);
        }
        else {
            Collision_Init(obj, &col, 1, 2u);
        }

        data->Action = 1;
    }
    else {
        ObjectMaster* boss = (ObjectMaster*)obj->Data1->LoopData;

        if (CurrentLevel == LevelIDs_Zero && boss->Data1->Action == 9)
            return;

        if (!boss || !boss->Data1) {
            CheckThingButThenDeleteObject(obj);
            return;
        }

        if (EntityData1Ptrs[0]->CharID != Characters_Gamma)
            return;

        data->Position = boss->Data1->Position;
        data->Position.y += 10;


        if (OhNoImDead(obj->Data1, (ObjectData2*)obj->Data2))
        {
            CheckThingButThenDeleteObject(obj);

            //if it is set, don't reload the target object
            if (data->CharID == 1)
                return;

            ObjectMaster* target = LoadObject((LoadObj)(LoadObj_Data1 | LoadObj_Data2), 2, TargetableEntity);
            target->Data1->LoopData = (Loop*)boss;
        }
        else
        {
            AddToCollisionList(data);
        }
    }
}

//Delete gamma shot on target
void Remove_TargetCursor(ObjectMaster* obj) {

    EntityData1* data = obj->Data1;

    if (data) {
        if (data->Status & Status_Hurt) {
            E102KillCursor((task*)obj);
        }
    }
}

//Allow gamma to target object
void Check_AllocateObjectData2(ObjectMaster* obj, EntityData1* data1)
{
    if (!obj || !data1)
        return;

    //if one of the player is gamma, init the target thing
    for (int i = 0; i < 8; i++) {

        if (!EntityData1Ptrs[i])
            continue;

        if (EntityData1Ptrs[i]->CharID == Characters_Gamma)
        {
            if (!data1->Action)
            {
                AllocateObjectData2(obj, data1);
                ObjectData2_SetStartPosition(obj->Data1, (ObjectData2*)obj->Data2);
            }

            Remove_TargetCursor(obj);
        }
    }
}