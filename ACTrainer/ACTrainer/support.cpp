#include "support.h"

void initializeVars(patchCheatStruct* noRecoilStruct, patchCheatStruct* infiniteAmmoStruct, changeValueStruct* weaponDamage, entityInfo* eInfo, uintptr_t baseAddr)
{
    noRecoilStruct->numBytesToPatch = 10;
    noRecoilStruct->originalBytes = new char[noRecoilStruct->numBytesToPatch];
    char originalBytes[] = { '\x50', '\x8d', '\x4c', '\x24', '\x1c', '\x51', '\x8b', '\xce', '\xff', '\xd2' };
    memcpy(noRecoilStruct->originalBytes, originalBytes, noRecoilStruct->numBytesToPatch);
    noRecoilStruct->instructionOffset = 0x63786;
    noRecoilStruct->patched = false;

    infiniteAmmoStruct->numBytesToPatch = 2;
    infiniteAmmoStruct->originalBytes = new char[infiniteAmmoStruct->numBytesToPatch];
    infiniteAmmoStruct->originalBytes[0] = '\xff';
    infiniteAmmoStruct->originalBytes[1] = '\x0e';
    infiniteAmmoStruct->instructionOffset = 0x637e9;
    infiniteAmmoStruct->patched = false;

    weaponDamage->amountDesired = 0x300;
    weaponDamage->changed = false;
    weaponDamage->checkPrevValue = false;
    weaponDamage->dynamic_offset = 0xFC300; //first weapon data structure
    weaponDamage->offSets = { 0x10c }; // offset to weapon damage.

    eInfo->localPlayerObjPtr = reinterpret_cast<PlayerObj*>(findDMAAddy(baseAddr + 0x10F4F4, { 0 }));
    eInfo->entityListPtr = reinterpret_cast<entityList*>(findDMAAddy(baseAddr + 0x10F4F8, { 0 }));

    memcpy(&eInfo->numOfEntities, (BYTE*)(baseAddr + 0x10F4FC), sizeof(int32_t));
}

void cleanup(Cheats cheatObj, patchCheatStruct infiniteAmmoStruct, patchCheatStruct noRecoilStruct, entityInfo* eInfo)
{
    std::cout << "[!!] Hacking program is closing attempting to clean up memory space...." << std::endl;
    //we are exiting unpatch any patched memory spaces
    if (infiniteAmmoStruct.patched)
    {
        std::cout << "[!!] Unpatching the infinite ammo hack.." << std::endl;
        cheatObj.PatchAnything(infiniteAmmoStruct);
    }
    if (noRecoilStruct.patched)
    {
        std::cout << "[!!] Unpatching the Zero Recoil hack.." << std::endl;
        cheatObj.PatchAnything(noRecoilStruct);
    }

    //when exiting the cheat engine we set the hp back to 100 regardless of what the changed value is.
    std::cout << "[!!] Setting hp back to 100.." << std::endl;
    eInfo->localPlayerObjPtr->PlayerHP = 100;

    //set player score back to previous value
    std::cout << "[!!] Setting player score back to previous value" << std::endl;
    if (eInfo->localPlayerObjPtr->playerScore >= 1337)
    {
        eInfo->localPlayerObjPtr->playerScore -= 1337;
    }

    std::cout << "[*] Exiting Cleanly.." << std::endl;

    if (!FreeConsole())
    {
        std::cout << GetLastError() << std::endl;
    }
    fclose(cheatObj.fPtr);
    CloseHandle(cheatObj.hwndConsole);
    return;
}

void printHackConsole(consoleBools cBools, entityInfo einfo, Vector3 beaconPos)
{
    system("cls");
    for (int i = 0; i < 100; i++)
        printf("-");
    printf("\n");
    printf("%50s\n", "BREADMAN'S ASSAULT CUBE HACK ENGINE");
    printf("%55s\n", "Internal DLL Injected by Remote DLL Injector");
    for (int i = 0; i < 100; i++)
        printf("-");
    printf("\n");

    printf("\n%-75s%s\n", "[Hacks]", "[Current Status]\n");
    printf("%-75s\n", "[NUMPAD0] Exit Hack Engine and Return Program to Normal State\n");

    printf("%-75s%s\n", "[NUMPAD1] Infinite Ammo", (cBools.num1Status ? "--> ON <--\n" : "--> OFF <--\n"));
    printf("%-75s%s\n", "[NUMPAD2] Infinite HP", (cBools.num2Status ? "--> ON <--\n" : "--> OFF <--\n"));
    printf("%-75s%s\n", "[NUMPAD3] Zero Recoil", (cBools.num3Status ? "--> ON <--\n" : "--> OFF <--\n"));
    printf("%-75s%s\n", "[NUMPAD4] Change Player Score to 1337", (cBools.num4Status ? "--> ON <--\n" : "--> OFF <--\n"));
    printf("%-75s%s%.3f, %.3f, %.3f]\n\n", 
        (cBools.num5status ? "[NUMPAD5] *TELEPORT* Back to Beacon" : "[NUMPAD5] Set *TELEPORT* Beacon"),
        (cBools.num5status ? "[*] Beacon Pos: [" : "[*] Curr Pos: ["),
        (cBools.num5status ? beaconPos.x : einfo.localPlayerObjPtr->PlayerPos.x),
        (cBools.num5status ? beaconPos.y : einfo.localPlayerObjPtr->PlayerPos.y),
        (cBools.num5status ? beaconPos.z : einfo.localPlayerObjPtr->PlayerPos.z));
    printf("%-75s%s\n", "[NUMPAD6] One Shot Kills for Everyone", (cBools.num6status ? "--> ON <--\n" : "--> OFF <--\n"));

}