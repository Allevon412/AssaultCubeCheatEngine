#pragma once

#include "Cheats.h"

void cleanup(Cheats cheatObj, patchCheatStruct infiniteAmmoStruct, patchCheatStruct noRecoilStruct, changeValueStruct infiniteHP, changeValueStruct playerScore);
void printHackConsole(BOOL num1Status, BOOL num2Status, BOOL num3Status, BOOL num4Status, playerPosStruct currPlayerPos, BOOL num6status);
void initializeVars(patchCheatStruct* noRecoilStruct, patchCheatStruct* infiniteAmmoStruct, 
	changeValueStruct* infiniteHP, changeValueStruct* playerScore, changeValueStruct* playerPosDataStruct,
	playerPosStruct* playerPos, changeValueStruct* weaponDamage);
