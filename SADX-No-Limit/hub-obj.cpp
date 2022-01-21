#include "pch.h"

Trampoline* ColCylinder_Main_t = nullptr;
Trampoline* ColCube_Main_t = nullptr;

    //hack a ton of object to make every character able to use them

//very ugly way to prevent some col in the set file.
void ColCylinder_Main_r(ObjectMaster* obj)
{

    if (CurrentLevel == LevelIDs_StationSquare && CurrentAct == 0)
    {
        NJS_POINT3 scale = { 4.1, 12, 32 };
        EntityData1* data = obj->Data1;

        if (data->Scale.x == scale.x && data->Scale.y == scale.y && data->Scale.z == scale.z)
        {
            return;
        }
    }

    ObjectFunc(origin, ColCylinder_Main_t->Target());
    origin(obj);
}

void ColCube_Main_r(ObjectMaster* obj)
{
    if (CurrentLevel == LevelIDs_MysticRuins && CurrentAct == 1)
    {
        NJS_POINT3 scale = { 22.3, 30, 39 };
        EntityData1* data = obj->Data1;

        if (data->Scale.x == scale.x && data->Scale.y == scale.y && data->Scale.z == scale.z)
        {
            if (IsAdventureComplete(SelectedCharacter))
                return;
        }
    }

    ObjectFunc(origin, ColCube_Main_t->Target());
    origin(obj);
}

bool isBarrierAllowed_r()
{
    if (IsAdventureComplete(SelectedCharacter))
    {
        return true;
    }

    return isBarrierAllowed();
}

bool sub_63EA90(char a1)
{
    if ((unsigned int)GetCharacterID(0) > 7)
    {
        return 0;
    }

    switch (a1)
    {
    case Characters_Sonic:
        if (!GetEventFlag((EventFlags)FLAG_SONIC_CLEAR_TWINKLEPARK))
        {
            break;
        }
        return GetEventFlag((EventFlags)FLAG_SONIC_CLEAR_HIGHWAY);
        break;
    case Characters_Amy:
        if (!GetEventFlag((EventFlags)FLAG_AMY_CLEAR_TWINKLEPARK))
        {
            break;
        }
        return GetEventFlag((EventFlags)FLAG_AMY_CLEAR_HOTSHELTER);
        break;
    case Characters_Big:
        if (GetEventFlag((EventFlags)FLAG_BIG_CLEAR_TWINKLEPARK))
        {
            return GetEventFlag((EventFlags)FLAG_BIG_CLEAR_SNOW);
        }

        break;
    }

    if (IsAdventureComplete(SelectedCharacter))
    {
        return 1;
    }

    return 0;
}

void __cdecl OTwindoor_r(ObjectMaster* obj)
{
    if (!ClipSetObject(obj))
    {
        Collision_Init(obj, (CollisionData*)0x2BC0CE0, 5, 4u);
        if (sub_63EA90(CurrentCharacter))
        {
            obj->MainSub = (ObjectFuncPtr)0x63ED60;
        }
        else
        {
            obj->MainSub = (ObjectFuncPtr)0x63EDD0;
        }
        obj->DisplaySub = (ObjectFuncPtr)0x63EB30;
    }
}

int IsCarAllowed_r()
{
    if (CurrentCharacter != Characters_Sonic && CurrentCharacter != Characters_Big)
    {
        return 1;
    }
    else {
        return isCarAllowed();
    }
}

bool ChangeSceneMR_r(int a1)
{

    if (!IsAdventureComplete(SelectedCharacter))
        return ChangeSceneMR_(a1);

    int level = 0;
    int act = 0;

    switch (a1)
    {
    case 0:
        level = LevelIDs_RedMountain;

        if (CurrentCharacter == Characters_Gamma || CurrentCharacter == Characters_Knuckles)
            return ChangeSceneMR_(a1);

        break;
    case 1:
        level = LevelIDs_IceCap;

        if (CurrentCharacter == Characters_Tails || CurrentCharacter == Characters_Big)
            return ChangeSceneMR_(a1);

        break;
    case 3:
        level = LevelIDs_FinalEgg;

        if (CurrentCharacter == Characters_Amy)
            return ChangeSceneMR_(a1);

        break;
    case 5:
        level = LevelIDs_MysticRuins;
        act = 3;
        SetLevelEntrance(0);
        break;
    case 6:
        level = LevelIDs_LostWorld;
        break;
    case 8:
        level = LevelIDs_SandHill;
        break;
    default:
        return ChangeSceneMR_(a1);
    }

    j_SetNextLevelAndAct_CutsceneMode(level, act);
    return 1;
}

static void __declspec(naked) ChangeSceneMR_ASM()
{
    __asm
    {
        push ebx
        call ChangeSceneMR_r
        pop ebx
        retn
    }
}

int __cdecl GetCharacterIDSkyDeck_r(char index)
{
    if (IsAdventureComplete(SelectedCharacter) && CurrentCharacter != Characters_Knuckles)
    {
        return Characters_Sonic;
    }
    else {
        return GetCharacterID(index);
    }
}

void init_HubObjectsHack() {

    WriteCall((void*)0x639941, IsCarAllowed_r);
    WriteJump(OTwindoor, OTwindoor_r);


    //hub world open area
    WriteCall((void*)0x5395C5, ChangeSceneMR_ASM);
    WriteCall((void*)0x63A110, isBarrierAllowed_r);


    //key door etc.
    WriteCall((void*)0x53C632, GetCharacterID_r);
    //icecap door
    WriteCall((void*)0x53E210, GetCurCharacter_r);

    //trick the game to make it think we are playing Sonic so everything is open
    
    //WV Entrance
    WriteCall((void*)0x536E40, GetCurCharacter_r);
    
    //island door
    WriteCall((void*)0x53F302, GetCharacterID_r);
    WriteCall((void*)0x53F3A1, GetCharacterID_r);
    WriteCall((void*)0x53F206, GetCharacterID_r);

    //Red Mountain door
    WriteCall((void*)0x53F922, GetCharacterID_r);
    WriteCall((void*)0x53E675, GetCharacterID_r);
    WriteCall((void*)0x53E5E9, GetCharacterID_r);
    WriteCall((void*)0x53E8A3, GetCharacterID_r);

    //kiki cage
    WriteCall((void*)0x53F97D, GetCharacterID_r);

    //lw temple
    WriteCall((void*)0x532E62, GetCharacterID_r);
    WriteCall((void*)0x532E8F, GetCharacterID_r);

    //final egg entrance
    WriteCall((void*)0x53EDF0, GetCharacterID_r);
    WriteCall((void*)0x53ED30, GetCharacterID_r);
    WriteCall((void*)0x538550, GetCharacterID_r);    
    
    //Speed Highway Shutter
    WriteCall((void*)0x63A589, GetCharacterID_r);    
    WriteCall((void*)0x63A2A2, GetCharacterID_r);

    //Speed Highway Elevator
    WriteCall((void*)0x638CC2, GetCharacterID_r);
    
    //Casino door
    WriteCall((void*)0x6383E2, GetCharacterID_r);

    //Egg Carrier Stuff
    WriteCall((void*)0x5240CA, GetCharacterID_r);   
    WriteCall((void*)0x52B475, GetCharacterGamma_r);
    //Sky Deck Entrance
    WriteCall((void*)0x51DEB1, GetCharacterIDSkyDeck_r);
   // WriteCall((void*)0x524F2F, GetCharacterID_r);    
   WriteCall((void*)0x524EC6, GetCharacterID_r);

    ColCylinder_Main_t = new Trampoline((int)ColCylinder_Main, (int)ColCylinder_Main + 0x6, ColCylinder_Main_r);
    ColCube_Main_t = new Trampoline((int)ColCube_Main, (int)ColCube_Main + 0x6, ColCube_Main_r);
}

