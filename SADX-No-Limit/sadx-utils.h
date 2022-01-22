#pragma once

FunctionPointer(void, PResetPosition, (EntityData1* data1, EntityData2* a2, CharObj2* a3), 0x43EE70);

FunctionPointer(int, isCarAllowed, (), 0x639740);

static const void* const tpDoorPtr = (void*)0x63EA90;
static signed int isTPDoorOpen(char a1)
{
	signed int result;

	__asm
	{
		push[a1]
		call tpDoorPtr
		mov eax, result
	}
	return result;
}

static const void* const ChangeSceneMRPtr = (void*)0x539220;
static BOOL ChangeSceneMR_(int a1)
{
	BOOL result;

	__asm
	{
		mov ebx, a1
		call ChangeSceneMRPtr
		mov eax, result
	}
	return result;
}

DataPointer(unsigned char, SelectedCharacter, 0x3B2A2FD);
FunctionPointer(bool, isBarrierAllowed, (), 0x639A30);

ObjectFunc(InvisibleWallCasino, 0x5d03a0);
ObjectFunc(SDCannon, 0x5f84e0);
ObjectFunc(SDCannonS1, 0x5f9710);
ObjectFunc(SDCannonS2, 0x5f8e00);