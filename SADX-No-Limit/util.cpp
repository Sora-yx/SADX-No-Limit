#include "pch.h"


//trick the game to make a character able to access every areas

int __cdecl GetCharacterID_r(char index)
{
    if (IsAdventureComplete(SelectedCharacter))
    {
        return Characters_Sonic;
    }
    else {
        return GetCharacterID(index);
    }
}

int __cdecl GetCharacterGamma_r(char index)
{
    if (IsAdventureComplete(SelectedCharacter))
    {
        return Characters_Gamma;
    }
    else {
        return GetCharacterID(index);
    }
}

int __cdecl GetCharacterAmy_r(char index)
{
    if (IsAdventureComplete(SelectedCharacter))
    {
        return Characters_Amy;
    }
    else {
        return GetCharacterID(index);
    }
}


int __cdecl GetCurCharacter_r()
{
    if (IsAdventureComplete(SelectedCharacter))
    {
        return Characters_Sonic;
    }
    else {
        return GetCurrentCharacterID();

    }
}
