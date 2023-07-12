#include "Cheats.h"


BOOL Cheats::infiniteAnything(int32_t* targetData, UINT desiredData)
{
        //write value to desired location.
        if (!memcpy(targetData, &desiredData, sizeof(desiredData)))
        {
            return false;
        }

        return true;
    
}

BOOL Cheats::TeleportPlayer(entityInfo* eInfo, Vector3 beaconPos)
{

    memcpy(&eInfo->localPlayerObjPtr->PlayerPos.x, &beaconPos.x, sizeof(float));
  
    memcpy(&eInfo->localPlayerObjPtr->PlayerPos.y, &beaconPos.y, sizeof(float));

    memcpy(&eInfo->localPlayerObjPtr->PlayerPos.z, &beaconPos.z, sizeof(float));

    return true;
}

/* 
* DEPRECATED FUNCTION
* 
BOOL Cheats::ReadPlayerPos(changeValueStruct dataStruct, playerPosStruct* playerPos)
{
    uintptr_t dynamicBaseAddr = baseAddr + dataStruct.dynamic_offset;
    uintptr_t valueOffset = findDMAAddy(dynamicBaseAddr, dataStruct.offSets);
    if (!ReadProcessMemory(GetCurrentProcess(), (BYTE*)valueOffset, &playerPos->xyzPos[0], sizeof(&playerPos->xyzPos[0]), 0))
    {
        return false;
    }
    if(!ReadProcessMemory(GetCurrentProcess(), (BYTE*)valueOffset + sizeof(&playerPos->xyzPos[0]), &playerPos->xyzPos[1], sizeof(&playerPos->xyzPos[0]), 0))
    {
        return false;
    }
    if (!ReadProcessMemory(GetCurrentProcess(), (BYTE*)valueOffset + (sizeof(&playerPos->xyzPos[0]) * 2), &playerPos->xyzPos[2], sizeof(&playerPos->xyzPos[0]), 0))
    {
        return false;
    }
    return true;
}
*/

BOOL Cheats::PatchAnything(patchCheatStruct cheatStruct)
{
    //perform the patching operation if instructions are currently unpatched.
    if (!cheatStruct.patched)
    {
        //create our nop sled to patch out the intended instructions.
        char* nop = new char[cheatStruct.numBytesToPatch + 1];
        memset(nop, '\x90', cheatStruct.numBytesToPatch + 1);

        //perform patching operation.
        DWORD oldprotect;
        if (!VirtualProtect((BYTE*)baseAddr + cheatStruct.instructionOffset, cheatStruct.numBytesToPatch, PAGE_EXECUTE_READWRITE, &oldprotect))
        {
            //TODO: delete bytes read
            delete[] nop;
            return false;
        }
        if (!memcpy((BYTE*)baseAddr + cheatStruct.instructionOffset, nop, cheatStruct.numBytesToPatch))
        {
            delete[] nop;
            return false;
        }
        if (!VirtualProtect((BYTE*)baseAddr + cheatStruct.instructionOffset, cheatStruct.numBytesToPatch, oldprotect, &oldprotect))
        {
            delete[] nop;
            return false;
        }
        delete[] nop;
        return true;
    }
    else
    {
        //perform patching operation.
        DWORD oldprotect;
        if (!VirtualProtect((BYTE*)baseAddr + cheatStruct.instructionOffset, cheatStruct.numBytesToPatch, PAGE_EXECUTE_READWRITE, &oldprotect))
        {

            return false;
        }
        if (!memcpy((BYTE*)baseAddr + cheatStruct.instructionOffset, cheatStruct.originalBytes, cheatStruct.numBytesToPatch))
        {

            return false;
        }
        if (!VirtualProtect((BYTE*)baseAddr + cheatStruct.instructionOffset, cheatStruct.numBytesToPatch, oldprotect, &oldprotect))
        {
            return false;
        }
        return true;
    }
}

BOOL Cheats::readWeaponData(UINT offset, weaponObj* wObj)
{
    UINT weaponDataStructureOffset = 0xFC300;
    UINT weaponDamageOffset = 0x10c;
    
    
    BYTE weaponNameBytes[25];
    memcpy(weaponNameBytes, (BYTE*)baseAddr + weaponDataStructureOffset + offset, sizeof(weaponNameBytes));
    wObj->weaponName = std::string(reinterpret_cast<char*>(weaponNameBytes), sizeof(weaponNameBytes)); 

    UINT value = 0;
    memcpy(&value, (BYTE*)baseAddr + weaponDataStructureOffset + offset + weaponDamageOffset, sizeof(BYTE) * 2);
    wObj->value = value;

    return true;
}
BOOL Cheats::writeWeaponData(UINT offset, weaponObj* wObj, BOOL status)
{
    if (status)
    {
        UINT weaponDataStructureOffset = 0xFC300;
        UINT weaponDamageOffset = 0x10c;
        char* tempName;
        tempName = new char[25];
        UINT oneShotDamageValue = 0x300;
        
        //get weapon name.
        memcpy(tempName, (BYTE*)baseAddr + weaponDataStructureOffset + offset, sizeof(tempName));

        //ensure the weapon name matches the one we think we're editing.
        if (!_strcmpi(tempName, wObj->weaponName.c_str()))
        {
            std::cout << "[!] weaponNames do not match. Please figure it out." << std::endl;
            return false;
        }
        //write one shot damage capability for the weapon.
        memcpy((BYTE*)baseAddr + weaponDataStructureOffset + offset + weaponDamageOffset, &oneShotDamageValue, sizeof(BYTE) * 2);

        return true;
    }
    else
    {

        UINT weaponDataStructureOffset = 0xFC300;
        UINT weaponDamageOffset = 0x10c;
        char* tempName;
        tempName = new char[25];

        //get weapon name.
        memcpy(tempName, (BYTE*)baseAddr + weaponDataStructureOffset + offset, sizeof(tempName));

        //ensure the weapon name matches the one we think we're editing.
        if (!_strcmpi(tempName, wObj->weaponName.c_str()))
        {
            std::cout << "[!] weaponNames do not match. Please figure it out." << std::endl;
            return false;
        }
        //revert the damage to it's normal level.
        memcpy((BYTE*)baseAddr + weaponDataStructureOffset + offset + weaponDamageOffset, &wObj->value, sizeof(BYTE) * 2);

        return true;
    }
    

}

void Cheats::getNecessaryVars()
{
    //get module base address
    baseAddr = (uintptr_t)GetModuleBaseAddr("ac_client.exe");

    
    AllocConsole();

    // Get the handle to the console window
    hwndConsole = GetConsoleWindow();

    // You can modify the console window properties if needed
    // For example, to set the window title:
    SetConsoleTitle("BreadMan's Assault Cube Hack Engine");

    freopen_s(&fPtr, "CONOUT$", "w", stdout);


  
}