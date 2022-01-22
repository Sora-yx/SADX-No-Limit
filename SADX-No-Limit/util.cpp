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

int __cdecl GetCharacterKnux_r(char index)
{
    if (IsAdventureComplete(SelectedCharacter))
    {
        return Characters_Knuckles;
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

int __cdecl GetCharacterHotShelter_r(char index)
{
    if (IsAdventureComplete(SelectedCharacter) && CurrentCharacter != Characters_Big && CurrentCharacter != Characters_Gamma)
    {
        return Characters_Amy;
    }
    else {
        return GetCharacterID(index);
    }
}


int __cdecl GetCurCharacterHS_r()
{
    if (IsAdventureComplete(SelectedCharacter) && CurrentCharacter != Characters_Big && CurrentCharacter != Characters_Gamma)
    {
        return Characters_Amy;
    }
    else {
        return GetCurrentCharacterID();

    }
}

int __cdecl GetCharacterIDSkyDeck_r(char index)
{
    if (IsAdventureComplete(SelectedCharacter) && CurrentCharacter != Characters_Knuckles && CurrentCharacter != Characters_Tails)
    {
        return Characters_Sonic;
    }
    else {
        return GetCharacterID(index);
    }
}

int __cdecl GetCharacterSD_r()
{
    if (IsAdventureComplete(SelectedCharacter) && CurrentCharacter != Characters_Knuckles && CurrentCharacter != Characters_Tails)
    {
        return Characters_Sonic;
    }
    else {
        return GetCurrentCharacterID();
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
