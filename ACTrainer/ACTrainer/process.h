#pragma once

#include <vector>
#include <windows.h>
#include <TlHelp32.h>

DWORD getProcId(const char* procName);

uintptr_t GetModuleBaseAddr(DWORD procId, const char* modName);

uintptr_t findDMAAddy(uintptr_t pt, std::vector<unsigned int> offsets);