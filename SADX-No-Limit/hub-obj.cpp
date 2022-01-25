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


int ChangeSceneMR_r(int a1)
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
    case 4:
        level = LevelIDs_MysticRuins;
        act = 2;
        SetLevelEntrance(4);
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

void init_HubObjectsHack() {

    //trick the game to make it think we are playing a specific character so everything is open
    
    //sewers 
    WriteCall((void*)0x639941, IsCarAllowed_r);   
    WriteCall((void*)0x636B79, GetCharacterBig_r);

    //TP Entrance
    WriteCall((void*)0x63EA92, GetCharIDTPDoor_r);   
    WriteCall((void*)0x63DBB2, GetCharIDTPDoor_r);

    //Hotel Cas back door
    WriteCall((void*)0x630972, GetCharacterID_r);    

    //train station back door
    WriteCall((void*)0x638882, GetCharacterID_r);

    //hub world open area
    WriteCall((void*)0x5395C5, ChangeSceneMR_ASM);
    WriteCall((void*)0x63A110, isBarrierAllowed_r);

    //key door etc.
    WriteCall((void*)0x53C632, GetCharacterID_r);
    //icecap door
    WriteCall((void*)0x53E210, GetCurCharacter_r);
 
    //WV Entrance
    WriteCall((void*)0x536E40, GetCurCharacter_r);

    //cave entry
    WriteCall((void*)0x534572, GetCharacterID_r);
    
    //island door
    WriteCall((void*)0x53F302, GetCharacterID_r);
    WriteCall((void*)0x53F3A1, GetCharacterID_r);
    WriteCall((void*)0x53F206, GetCharacterID_r);

    //Red Mountain door
    WriteCall((void*)0x53F922, GetCharacterID_r);
    WriteCall((void*)0x53E675, GetCharacterID_r);
    WriteCall((void*)0x53E5E9, GetCharacterID_r);
    WriteCall((void*)0x53E8A3, GetCurCharacter_r);

    //kiki cage
    WriteCall((void*)0x53F97D, GetCharacterID_r);

    //lw temple
    WriteCall((void*)0x532E62, GetCharacterID_r);
    WriteCall((void*)0x532E8F, GetCharacterID_r);

    //final egg entrance
    WriteCall((void*)0x53EDF0, GetCurCharacter_r);
    WriteCall((void*)0x53ED30, GetCurCharacter_r);
    WriteCall((void*)0x538550, GetCurCharacter_r);    
    
    //Speed Highway Shutter
    WriteCall((void*)0x63A589, GetCharacterID_r);    
    WriteCall((void*)0x63A2A2, GetCharacterID_r);

    //Speed Highway Elevator
    WriteCall((void*)0x638CC2, GetCharacterID_r);

    //Speed Highway Knuckles Entrance
    WriteCall((void*)0x636BF2, GetCharacterKnux_r);
    
    //Casino door
    WriteCall((void*)0x6383E2, GetCharacterID_r);

    //Egg Carrier Stuff
    WriteCall((void*)0x5240CA, GetCharacterID_r);   
    WriteCall((void*)0x52B475, GetCharacterGamma_r);

    //Sky Deck Entrance
    WriteCall((void*)0x51DEB1, GetCharacterSD_r);  
   WriteCall((void*)0x524EC6, GetCurCharacter_r);
   WriteCall((void*)0x525020, GetCharacterSD_r);
   //SD Knux entrance
   WriteCall((void*)0x51E23D, GetCurCharKnux_r);

   //Hot Shelter Entry
   WriteCall((void*)0x52D5DF, GetCurCharacterHS_r);
   WriteCall((void*)0x52D576, GetCurCharacterHS_r);
   WriteCall((void*)0x52D6C3, GetCurCharacterHS_r);

   //Sand Hill Entry
   WriteCall((void*)0x53EB16, GetCharacterMiles_r);  
   WriteCall((void*)0x53EB56, GetCharacterMiles_r);  
   WriteCall((void*)0x53EAF2, GetCharacterMiles_r);


    ColCylinder_Main_t = new Trampoline((int)ColCylinder_Main, (int)ColCylinder_Main + 0x6, ColCylinder_Main_r);
    ColCube_Main_t = new Trampoline((int)ColCube_Main, (int)ColCube_Main + 0x6, ColCube_Main_r);
}

