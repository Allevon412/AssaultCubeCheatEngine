#include "Cheats.h"


BOOL Cheats::infiniteAnything(changeValueStruct* valueStruct)
{
    if (valueStruct->changed)
    {
        //resolve base address of the pointer chain
        uintptr_t dynamicPtrBaseAddr = baseAddr + valueStruct->dynamic_offset;

        //resolve value pointer chain
        uintptr_t valueOffset = findDMAAddy(dynamicPtrBaseAddr, valueStruct->offSets);

        //read value of desired location.
        // only do this the first time since previousValue will be be non-zero after this read.
        if (valueStruct->checkPrevValue)
        {
            if (!ReadProcessMemory(GetCurrentProcess(), (BYTE*)valueOffset, &valueStruct->previousValue, sizeof(valueStruct->previousValue), 0))
            {
                return false;
            }
        }

        //write value to desired location.
        if (!WriteProcessMemory(GetCurrentProcess(), (BYTE*)valueOffset, &valueStruct->amountDesired, sizeof(valueStruct->amountDesired), 0))
        {
            return false;
        }

        return true;
    }
    else
    {
        uintptr_t dynamicPtrBaseAddr = baseAddr + valueStruct->dynamic_offset;
        uintptr_t valueOffset = findDMAAddy(dynamicPtrBaseAddr, valueStruct->offSets);

        //write value to desired location.
        if (!WriteProcessMemory(GetCurrentProcess(), (BYTE*)valueOffset, &valueStruct->previousValue, sizeof(valueStruct->previousValue), 0))
        {
            return false;
        }

        return true;
    }
    
}

BOOL Cheats::TeleportPlayer(changeValueStruct dataStruct, playerPosStruct* playerPos)
{
    uintptr_t dynamicBaseAddr = baseAddr + dataStruct.dynamic_offset;
    uintptr_t valueOffset = findDMAAddy(dynamicBaseAddr, dataStruct.offSets);
    if (!WriteProcessMemory(GetCurrentProcess(), (BYTE*)valueOffset, &playerPos->xyzPos[0], sizeof(&playerPos->xyzPos[0]), 0))
    {
        return false;
    }
    if (!WriteProcessMemory(GetCurrentProcess(), (BYTE*)valueOffset + sizeof(&playerPos->xyzPos[0]), &playerPos->xyzPos[1], sizeof(&playerPos->xyzPos[0]), 0))
    {
        return false;
    }
    if (!WriteProcessMemory(GetCurrentProcess(), (BYTE*)valueOffset + (sizeof(&playerPos->xyzPos[0]) * 2), &playerPos->xyzPos[2], sizeof(&playerPos->xyzPos[0]), 0))
    {
        return false;
    }
    return true;
}

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

BOOL Cheats::PatchAnything(patchCheatStruct cheatStruct)
{
    //perform the patching operation if instructions are currently unpatched.
    if (!cheatStruct.patched)
    {
        //create a space to read the intended instructions out of memory.
        char* bytesRead = new char[cheatStruct.numBytesToPatch];
        memset(bytesRead, 0, cheatStruct.numBytesToPatch);
        if (!ReadProcessMemory(GetCurrentProcess(), (BYTE*)baseAddr + cheatStruct.instructionOffset, bytesRead, cheatStruct.numBytesToPatch, 0))
        {
            std::cout << "Error reading memory to patch the program" << std::endl;
            return false;
        }

        //create our nop sled to patch out the intended instructions.
        char* nop = new char[cheatStruct.numBytesToPatch+1];
        memset(nop, '\x90', cheatStruct.numBytesToPatch+1);
        
        //compare original bytes with bytes read to make sure they match and we know we have the correct location.
        if (std::memcmp(cheatStruct.originalBytes, bytesRead, cheatStruct.numBytesToPatch) == 0)
        {
            //perform patching operation.
            DWORD oldprotect;
            if (!VirtualProtectEx(GetCurrentProcess(), (BYTE*)baseAddr + cheatStruct.instructionOffset, cheatStruct.numBytesToPatch, PAGE_EXECUTE_READWRITE, &oldprotect))
            {
                //TODO: delete bytes read
                delete[] nop;
                return false;
            }
            if (!WriteProcessMemory(GetCurrentProcess(), (BYTE*)baseAddr + cheatStruct.instructionOffset, nop, cheatStruct.numBytesToPatch, 0))
            {
                delete[] nop;
                return false;
            }
            if (!VirtualProtectEx(GetCurrentProcess(), (BYTE*)baseAddr + cheatStruct.instructionOffset, cheatStruct.numBytesToPatch, oldprotect, &oldprotect))
            {
                delete[] nop;
                return false;
            }
            delete[] nop;
            return true;
        }
        else
        {
            std::cout << "Error performing patching operation. The original bytes do match the bytes read" << std::endl;
            delete[] nop;
            return false;
        }
    }
    else
    {
        //perform unpatch operations using original bytes if instructions are currently patched.
        char* bytesRead = new char[cheatStruct.numBytesToPatch+1];
        memset(bytesRead, 0, cheatStruct.numBytesToPatch+1);
        if (!ReadProcessMemory(GetCurrentProcess(), (BYTE*)baseAddr + cheatStruct.instructionOffset, bytesRead, cheatStruct.numBytesToPatch, 0))
        {
            std::cout << "Error reading memory to patch the program" << std::endl;
            return false;
        }
        //create our nop sled to patch out the intended instructions.
        char* nop = new char[cheatStruct.numBytesToPatch+1];
        memset(nop, '\x90', cheatStruct.numBytesToPatch+1);

        //compare nop bytes with bytes read to make sure they match and we know we have the correct location.
        if (std::memcmp(nop, bytesRead, cheatStruct.numBytesToPatch) == 0)
        {
            //perform patching operation.
            DWORD oldprotect;
            if (!VirtualProtectEx(GetCurrentProcess(), (BYTE*)baseAddr + cheatStruct.instructionOffset, cheatStruct.numBytesToPatch, PAGE_EXECUTE_READWRITE, &oldprotect))
            {
                delete[] nop;
                return false;
            }
            if (!WriteProcessMemory(GetCurrentProcess(), (BYTE*)baseAddr + cheatStruct.instructionOffset, cheatStruct.originalBytes, cheatStruct.numBytesToPatch, 0))
            {
                delete[] nop;
                return false;
            }
            if (!VirtualProtectEx(GetCurrentProcess(), (BYTE*)baseAddr + cheatStruct.instructionOffset, cheatStruct.numBytesToPatch, oldprotect, &oldprotect))
            {
                delete[] nop;
                return false;
            }
            return true;
        }
        else
        {
            std::cout << "Error performing patching operation. The patched bytes do match the bytes read" << std::endl;
            delete[] nop;
            return false;
        }
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
        
        std::cout << "[*] address to be read: " << (BYTE*)baseAddr + weaponDataStructureOffset + offset << std::endl;
        //get weapon name.
        memcpy(tempName, (BYTE*)baseAddr + weaponDataStructureOffset + offset, sizeof(tempName));
        std::cout << "[*] Got the weapon name" << tempName;

        //ensure the weapon name matches the one we think we're editing.
        if (!_strcmpi(tempName, wObj->weaponName.c_str()))
        {
            std::cout << "[!] weaponNames do not match. Please figure it out." << std::endl;
            return false;
        }
        //write one shot damage capability for the weapon.
        memcpy((BYTE*)baseAddr + weaponDataStructureOffset + offset + weaponDamageOffset, &oneShotDamageValue, sizeof(BYTE) * 2);
        std::cout << "[*] Past the Memory Write call";

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
    baseAddr = (uintptr_t)GetModuleHandle(NULL);

    
    AllocConsole();

    // Get the handle to the console window
    hwndConsole = GetConsoleWindow();

    // You can modify the console window properties if needed
    // For example, to set the window title:
    SetConsoleTitle("BreadMan's Assault Cube Hack Engine");

    freopen_s(&fPtr, "CONOUT$", "w", stdout);


  
}
/* DEPRECATED CODE used for when the hacks were external to the process.
   *
BOOL Cheats::CloseHandles()
{
    if (CloseHandle(hProc))
    {
        return true;
    }
    else
    {
        return false;
    }
}
*/