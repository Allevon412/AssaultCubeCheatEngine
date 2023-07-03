#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>

#include "process.h"



struct patchCheatStruct
{
	DWORD numBytesToPatch;
	char* originalBytes;
	DWORD instructionOffset;
	BOOL patched;
};

struct changeValueStruct
{
	std::vector<unsigned int> offSets;
	UINT dynamic_offset;
	UINT amountDesired;
	UINT previousValue;
	BOOL checkPrevValue;
	BOOL changed;
};

struct weaponObj
{
    std::string weaponName;
	UINT value;
};

struct playerPosStruct
{
	std::vector<float> xyzPos;
};

class Cheats
{
private: 

public:
	//define constructor variables
	FILE* fPtr;
	HWND hwndConsole;

	//default variables necessary to run the infinite ammo cheat
	Cheats() {

	}

	//defining variables necesary for other cheats
	uintptr_t baseAddr = 0;

	void getNecessaryVars();


	// Cheats definitions
	BOOL infiniteAnything(changeValueStruct* valueStruct);
	BOOL PatchAnything(patchCheatStruct cheatStruct);
	BOOL TeleportPlayer(changeValueStruct dataStruct, playerPosStruct* playerPos);
	BOOL ReadPlayerPos(changeValueStruct dataStruct, playerPosStruct* playerPos);
	BOOL readWeaponData(UINT offset, weaponObj* wObj);
	BOOL writeWeaponData(UINT offset, weaponObj* wObj, BOOL status);
};



