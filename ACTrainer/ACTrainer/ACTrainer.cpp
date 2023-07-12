// ACTrainer.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <Windows.h>
#include <vector>
#include <iomanip>
#include <stdlib.h>


#include "process.h"
#include "Cheats.h"
#include "support.h"
#include "assaultCubeClasses.h"


DWORD WINAPI go(HMODULE hMod)
{
    
    //setup a cheatStructure for noRecoil Struct.
    patchCheatStruct noRecoilStruct;
    //setup a cheatStructure for infiniteAmmo (patch out the decrement ammo instruction)
    patchCheatStruct infiniteAmmoStruct;
    //setup data for infinite hp, high score.
    UINT desiredScore = 1337;
    UINT desiredHP = 999;

    //setup value struct for one shot kills on current weapon.
    changeValueStruct weaponDamage;
    weaponObj weaponArray[10];

    //setup structures for the player position to be read / edited.
    Vector3 beaconPos = { 0 };

    //set up cheater object
    Cheats cheatObj;

    //initialize base addr ptr.
    cheatObj.getNecessaryVars();
    entityInfo eInfo = { 0 };

    consoleBools consoleBools;
    consoleBools.num1Status = false, consoleBools.num2Status = false, consoleBools.num3Status = false, consoleBools.num4Status = false, consoleBools.num5status = false, consoleBools.num6status = false;
   
    //initialize our structures so we can easily obtain pointers to our data locations we want to change.
    initializeVars(&noRecoilStruct, &infiniteAmmoStruct, &weaponDamage, &eInfo, cheatObj.baseAddr);
    
    printHackConsole(consoleBools, eInfo, beaconPos);
    
    //define the DWORD var for determining whether the process has exited.
    DWORD dwExit = 0;
    do
    {

        // if numpad key is detected. Perform actions based on input.
        if (GetAsyncKeyState(VK_NUMPAD1) & 1)
        {
            consoleBools.num1Status = !consoleBools.num1Status;
            printHackConsole(consoleBools, eInfo, beaconPos);
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
            consoleBools.num2Status = !consoleBools.num2Status;
            printHackConsole(consoleBools, eInfo, beaconPos);

            //if we're turning our infiniteHP hack off. Let's set the value back to the previous value.
            if (!consoleBools.num2Status)
            {
                if (!(cheatObj.infiniteAnything(&eInfo.localPlayerObjPtr->PlayerHP, 100)))
                {
                    std::cout << "[!] Error attempting to set HP back to it's normal state";

                }
            }

        }
        if (GetAsyncKeyState(VK_NUMPAD3) & 1)
        {
            consoleBools.num3Status = !consoleBools.num3Status;
            printHackConsole(consoleBools, eInfo, beaconPos);
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
            consoleBools.num4Status = !consoleBools.num4Status;
            printHackConsole(consoleBools, eInfo, beaconPos);

            if (consoleBools.num4Status)
            {
                if (!cheatObj.infiniteAnything(&eInfo.localPlayerObjPtr->playerScore, eInfo.localPlayerObjPtr->playerScore + desiredScore))
                {
                    std::cout << "[!] Error switching score back Exiting!" << std::endl;
                    continue;
                }
            }
            else
            {
                UINT previousScore = eInfo.localPlayerObjPtr->playerScore - desiredScore;
                if (!cheatObj.infiniteAnything(&eInfo.localPlayerObjPtr->playerScore, previousScore))
                {
                    std::cout << "[!] Error switching score back Exiting!" << std::endl;
                    continue;
                }
            }
          
           
        }
        if (GetAsyncKeyState(VK_NUMPAD5) & 1)
        {   
            if (!consoleBools.num5status)
            {
                beaconPos.x = eInfo.localPlayerObjPtr->PlayerPos.x;
                beaconPos.y = eInfo.localPlayerObjPtr->PlayerPos.y;
                beaconPos.z = eInfo.localPlayerObjPtr->PlayerPos.z;
                
            }
            else
            {
                if (!cheatObj.TeleportPlayer(&eInfo, beaconPos))
                {
                    std::cout << "[!] Error teleporting player. Exiting!";
                    return -1;
                }
                beaconPos = { 0 };
                
            }
            consoleBools.num5status = !consoleBools.num5status;
            printHackConsole(consoleBools, eInfo, beaconPos);
            
        }
        if (GetAsyncKeyState(VK_NUMPAD6) & 1)
        {
            consoleBools.num6status = !consoleBools.num6status;

            if (consoleBools.num6status)
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
                    weaponArray[i].value = wObj.value;
                    weaponArray[i].weaponName = wObj.weaponName;
                    
                    if (!cheatObj.writeWeaponData(offsetToNextWeapon, &wObj, consoleBools.num6status))
                    {
                        std::cout << "[!] Error trying to write weapon data" << std::endl;
                        break;
                    }
                }
                printHackConsole(consoleBools, eInfo, beaconPos);
            }
            else
            {
                for (int i = 0; i < 10; i++)
                {
                    UINT offsetToNextWeapon = i * 0x12A;
                    if (!cheatObj.writeWeaponData(offsetToNextWeapon, &weaponArray[i], consoleBools.num6status))
                    {
                        std::cout << "[!] Error trying to revert weapon damage" << std::endl;
                        break;
                    }
                }
                printHackConsole(consoleBools, eInfo, beaconPos);
            }
        }
        if (GetAsyncKeyState(VK_NUMPAD0) & 1)
        {
            cleanup(cheatObj, infiniteAmmoStruct, noRecoilStruct, &eInfo);
            FreeLibraryAndExitThread(hMod, 0);
        }

        //part of the loop that will replace our current hp with what is defined as desirable amount above.
        if (consoleBools.num2Status)
        {
            //perform infinite loop for giving yourself infinite hp.
            if (!cheatObj.infiniteAnything(&eInfo.localPlayerObjPtr->PlayerHP, desiredHP))
            {
                std::cout << "[!] Error giving ourselves infinite health! Exiting!" << std::endl;
                return -1;
            }
        }

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
        //go(hModule);
        //return 0;
        
        HANDLE hThread = NULL;
        hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)go, hModule, 0, nullptr);
        if (hThread)
        {
            CloseHandle(hThread);
            return 0;
        }
        return -1;
        
        
        
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
}