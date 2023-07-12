#pragma once

#include "Cheats.h"
#include "assaultCubeClasses.h"

struct consoleBools
{
    BOOL num1Status, num2Status, num3Status, num4Status, num5status, num6status;
};

void cleanup(Cheats cheatObj, patchCheatStruct infiniteAmmoStruct, patchCheatStruct noRecoilStruct, entityInfo* eInfo);
void printHackConsole(consoleBools cBools, entityInfo einfo, Vector3 beaconPos);
void initializeVars(patchCheatStruct* noRecoilStruct, patchCheatStruct* infiniteAmmoStruct, changeValueStruct* weaponDamage, entityInfo* eInfo, uintptr_t baseAddr);
