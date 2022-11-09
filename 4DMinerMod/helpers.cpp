#include "helpers.hpp"

#include <Windows.h>
#include <iostream>
#include <cstdint>

void OpenConsole(){
    AllocConsole();
    FILE* in;
    FILE* out;
    freopen_s(&in, "conin$", "r", stdin);
    freopen_s(&out, "conout$", "w", stdout);
    freopen_s(&out, "conout$", "w", stderr);
}

void* VFTHook(_In_ void* lpVirtualTable, _In_ void* pHookMethod, _In_opt_ uintptr_t dwOffset) {
	uintptr_t dwVTable = *((uintptr_t*)lpVirtualTable);
	uintptr_t dwEntry = dwVTable + dwOffset;
	uintptr_t dwOrig = *((uintptr_t*)dwEntry);

	DWORD dwOldProtection;
	::VirtualProtect((LPVOID)dwEntry, sizeof(dwEntry),
		PAGE_EXECUTE_READWRITE, &dwOldProtection);

	*((uintptr_t*)dwEntry) = (uintptr_t)pHookMethod;

	::VirtualProtect((LPVOID)dwEntry, sizeof(dwEntry),
		dwOldProtection, &dwOldProtection);

	return (LPVOID)dwOrig;
}