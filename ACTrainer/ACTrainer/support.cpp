#include "support.h"

void initializeVars(patchCheatStruct* noRecoilStruct, patchCheatStruct* infiniteAmmoStruct,
    changeValueStruct* infiniteHP, changeValueStruct* playerScore, changeValueStruct* playerPosDataStruct,
    playerPosStruct* currPlayerPos, changeValueStruct* weaponDamage)
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

    infiniteHP->changed = false;
    infiniteHP->dynamic_offset = 0x10F4F4;
    infiniteHP->amountDesired = 6969;
    infiniteHP->offSets = { 0xf8 };
    infiniteHP->previousValue = 100;
    infiniteHP->checkPrevValue = false;

    playerScore->changed = false;
    playerScore->dynamic_offset = 0x10F4F4;
    playerScore->amountDesired = 1337;
    playerScore->offSets = { 0x1fc };
    playerScore->previousValue = 0;
    playerScore->checkPrevValue = true;

    playerPosDataStruct->changed = false;
    playerPosDataStruct->dynamic_offset = 0x10F4F4;
    playerPosDataStruct->offSets = { 0x34 };

    currPlayerPos->xyzPos = { 0.1,0.1,0.1 };

    weaponDamage->amountDesired = 0x300;
    weaponDamage->changed = false;
    weaponDamage->checkPrevValue = false;
    weaponDamage->dynamic_offset = 0xFC300; //first weapon data structure
    weaponDamage->offSets = { 0x10c }; // offset to weapon damage.
}

void cleanup(Cheats cheatObj, patchCheatStruct infiniteAmmoStruct, patchCheatStruct noRecoilStruct, changeValueStruct infiniteHP, changeValueStruct playerScore)
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
    infiniteHP.amountDesired = infiniteHP.previousValue;
    cheatObj.infiniteAnything(&infiniteHP);

    //set player score back to previous value
    std::cout << "[!!] Setting player score back to previous value" << std::endl;
    playerScore.amountDesired = playerScore.previousValue;
    cheatObj.infiniteAnything(&playerScore);

    std::cout << "[*] Exiting Cleanly.." << std::endl;

    if (!FreeConsole())
    {
        std::cout << GetLastError() << std::endl;
    }
    fclose(cheatObj.fPtr);
    CloseHandle(cheatObj.hwndConsole);
    return;
}

void printHackConsole(BOOL num1Status, BOOL num2Status, BOOL num3Status, BOOL num4Status, playerPosStruct currPlayerPos, BOOL num6status)
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

    printf("%-75s%s\n", "[NUMPAD1] Infinite Ammo", (num1Status ? "--> ON <--\n" : "--> OFF <--\n"));
    printf("%-75s%s\n", "[NUMPAD2] Infinite HP", (num2Status ? "--> ON <--\n" : "--> OFF <--\n"));
    printf("%-75s%s\n", "[NUMPAD3] Zero Recoil", (num3Status ? "--> ON <--\n" : "--> OFF <--\n"));
    printf("%-75s%s\n", "[NUMPAD4] Change Player Score to 1337", (num4Status ? "--> ON <--\n" : "--> OFF <--\n"));
    printf("%-75s%s%.3f%s%.3f%s%.3f%s\n", "[NUMPAD5] Change Player Pos *TELEPORT*", "[*] Curr Pos: [",
        currPlayerPos.xyzPos[0], ", ", currPlayerPos.xyzPos[1], ", ", currPlayerPos.xyzPos[2], "]\n");
    printf("%-75s%s\n", "[NUMPAD6] One Shot Kills for Everyone", (num6status ? "--> ON <--\n" : "--> OFF <--\n"));

}