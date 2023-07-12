#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>

#include "process.h"
#include "assaultCubeClasses.h"



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
	BOOL infiniteAnything(int32_t* targetData, UINT desiredData);
	BOOL PatchAnything(patchCheatStruct cheatStruct);
	BOOL TeleportPlayer(entityInfo* eInfo, Vector3 beaconPos);
	//BOOL ReadPlayerPos(changeValueStruct dataStruct, playerPosStruct* playerPos);
	BOOL readWeaponData(UINT offset, weaponObj* wObj);
	BOOL writeWeaponData(UINT offset, weaponObj* wObj, BOOL status);
};



