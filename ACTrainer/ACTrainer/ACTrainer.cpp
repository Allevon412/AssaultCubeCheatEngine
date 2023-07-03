// ACTrainer.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <Windows.h>
#include <vector>
#include <iomanip>

#include <stdlib.h>


#include "process.h"
#include "Cheats.h"
#include "support.h"


DWORD WINAPI go(HMODULE hMod)
{
    
    //setup a cheatStructure for noRecoil Struct.
    patchCheatStruct noRecoilStruct;
    //setup a cheatStructure for infiniteAmmo (patch out the decrement ammo instruction)
    patchCheatStruct infiniteAmmoStruct;
    //setup structure for infinite hp.
    changeValueStruct infiniteHP;
    //std::vector<unsigned int> ammoOffsets = { 0x374, 0x14, 0x0 };
    changeValueStruct playerScore;
    //setup value struct for one shot kills on current weapon.
    changeValueStruct weaponDamage;
    weaponObj weaponArray[10];

    //setup structures for the player position to be read / edited.
    changeValueStruct playerPosDataStruct;
    playerPosStruct currPlayerPos;

    //set up cheater object
    Cheats cheatObj;

    //initialize base addr ptr.
    cheatObj.getNecessaryVars();
    //initialize our structures so we can easily obtain pointers to our data locations we want to change.
    initializeVars(&noRecoilStruct, &infiniteAmmoStruct, &infiniteHP, &playerScore, &playerPosDataStruct, &currPlayerPos, &weaponDamage);

    cheatObj.ReadPlayerPos(playerPosDataStruct, &currPlayerPos);
    
    //intiailize status symbols for our cheats
    BOOL num1Status = false, num2Status = false, num3Status = false, num4Status = false, num6status = false;
    printHackConsole(num1Status, num2Status, num3Status, num4Status, currPlayerPos, num6status);
    
    //define the DWORD var for determining whether the process has exited.
    DWORD dwExit = 0;
    do
    {

        // if numpad key is detected. Perform actions based on input.
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            num1Status = !num1Status;
            printHackConsole(num1Status, num2Status, num3Status, num4Status, currPlayerPos, num6status);
            //perform patch operation to give yourself infinite ammo.
            if (!cheatObj.PatchAnything(infiniteAmmoStruct))
            {
                char msg[] = "[!] Error Patching the intended Bytes Exiting!";
                
                infiniteAmmoStruct.patched = false; // always set patched state to false here due to failure to complete the operation.
                return -1;
            }
            //flip the patched state in the struct to ensure the next time we press the key it will patch / unpatch based on the current state.
            infiniteAmmoStruct.patched = !infiniteAmmoStruct.patched;

        }
        if (GetAsyncKeyState(VK_NUMPAD2) & 1)
        {
            //infiniteHP inversion: infiniteHP = !infiniteHP
            infiniteHP.changed = !infiniteHP.changed;
            num2Status = !num2Status;
            printHackConsole(num1Status, num2Status, num3Status, num4Status, currPlayerPos, num6status);

            //if we're turning our infiniteHP hack off. Let's set the value back to the previous value.
            if (!infiniteHP.changed)
            {
                if (!(cheatObj.infiniteAnything(&infiniteHP)))
                {
                    std::cout << "[!] Error attempting to set HP back to it's normal state";

                }
            }

        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            num3Status = !num3Status;
            printHackConsole(num1Status, num2Status, num3Status, num4Status, currPlayerPos, num6status);
            //perform infinite loop for giving yourself infinite hp.
            if (!cheatObj.PatchAnything(noRecoilStruct))
            {
                std::cout << "[!] Error giving ourselves zero recoil! Exiting!" << std::endl;
                noRecoilStruct.patched = false; // always set patched state to false here due to failure to complete the operation.
                return -1;
            }

            //flip the patched state in the struct to ensure the next time we press the key it will patch / unpatch based on the current state.
            noRecoilStruct.patched = !noRecoilStruct.patched;

        }
        if (GetAsyncKeyState(VK_NUMPAD4) & 1)
        {
            num4Status = !num4Status;
            printHackConsole(num1Status, num2Status, num3Status, num4Status, currPlayerPos, num6status);
            playerScore.changed = !playerScore.changed;

            

            if (!cheatObj.infiniteAnything(&playerScore))
            {
                std::cout << "[!] Error switching score back Exiting!" << std::endl;
                playerScore.changed = false;
                continue;
            }
           
        }
        if (GetAsyncKeyState(VK_NUMPAD5) & 1)
        {
            currPlayerPos.xyzPos[2] = 5.0; //change z position to 5
            if (!cheatObj.TeleportPlayer(playerPosDataStruct, &currPlayerPos))
            {
                std::cout << "[!] Error teleporting player. Exiting!";
                return -1;
            }
            printHackConsole(num1Status, num2Status, num3Status, num4Status, currPlayerPos, num6status);

        }
        if (GetAsyncKeyState(VK_NUMPAD6) & 1)
        {
            num6status = !num6status;

            if (num6status)
            {
                weaponObj wObj;

                for (int i = 0; i < 10; i++)
                {
                    UINT offsetToNextWeapon = i * 0x12A;
                    if (!cheatObj.readWeaponData(offsetToNextWeapon, &wObj))
                    {
                        std::cout << "[!] Error trying to read weapon data" << std::endl;
                        break;
                    }
                    std::cout << "[*] Attempting to assign wObj to wArr" << std::endl;
                    weaponArray[i].value = wObj.value;
                    weaponArray[i].weaponName = wObj.weaponName;
                    std::cout << "[*] After assignment" << std::endl;
                    if (!cheatObj.writeWeaponData(offsetToNextWeapon, &wObj, num6status))
                    {
                        std::cout << "[!] Error trying to write weapon data" << std::endl;
                        break;
                    }
                }
                printHackConsole(num1Status, num2Status, num3Status, num4Status, currPlayerPos, num6status);
            }
            else
            {
                for (int i = 0; i < 10; i++)
                {
                    UINT offsetToNextWeapon = i * 0x12A;
                    if (!cheatObj.writeWeaponData(offsetToNextWeapon, &weaponArray[i], num6status))
                    {
                        std::cout << "[!] Error trying to revert weapon damage" << std::endl;
                        break;
                    }
                }
                printHackConsole(num1Status, num2Status, num3Status, num4Status, currPlayerPos, num6status);
            }
        }
        if (GetAsyncKeyState(VK_NUMPAD0) & 1)
        {
            cleanup(cheatObj, infiniteAmmoStruct, noRecoilStruct, infiniteHP, playerScore);
            FreeLibraryAndExitThread(hMod, 0);
        }

        //part of the loop that will replace our current hp with what is defined as desirable amount above.
        if (infiniteHP.changed)
        {
            //perform infinite loop for giving yourself infinite hp.
            if (!cheatObj.infiniteAnything(&infiniteHP))
            {
                std::cout << "[!] Error giving ourselves infinite health! Exiting!" << std::endl;
                return -1;
            }
        }
        
        cheatObj.ReadPlayerPos(playerPosDataStruct, &currPlayerPos);
        //Sleep for a short time before checking again.
        Sleep(10);

    } while (GetExitCodeProcess(GetCurrentProcess(), &dwExit) && dwExit == STILL_ACTIVE);
    
    if (!FreeConsole())
    {
        std::cout << GetLastError() << std::endl;
    }
    fclose(cheatObj.fPtr);
    CloseHandle(cheatObj.hwndConsole);
    FreeLibraryAndExitThread(hMod, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {

    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)go, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
}