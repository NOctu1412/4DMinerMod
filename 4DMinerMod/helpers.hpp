#pragma once

#include <cstdint>

void OpenConsole();

void* VFTHook(void* lpVirtualTable, void* pHookMethod, uintptr_t dwOffset);