#include <Windows.h>
#include <iostream>
#include <detours.h>

#include "helpers.hpp"
#include "StateManager.hpp"
#include "States.hpp"

HMODULE hMod;

typedef void(__fastcall* playerUpdateFunc)(Player* thiz, void* window, World* world);
playerUpdateFunc ogFunc;

void __fastcall playerUpdateHook(Player* p, void* window, World* world) {
    if (p->targetingBlock && p->keys.leftMouseDown) { //INSTANT BREAK//
        p->targetDamage = 1.0;
    }
    
    //FLY//
    p->vel.x = 0;
    if (p->keys.space)
        p->vel.x = 0.12;
    if (p->keys.ctrl)
        p->vel.x = -0.12;

    ogFunc(p, window, world); //CALL THE ORIGINAL METHOD//

    p->vel.x = 0; //FLY//
}

void MainThread() {
    OpenConsole();

    //get module base addr//
    uintptr_t gameAddr = (uintptr_t)GetModuleHandleA("4D Miner.exe");

    //hook player update//
    ogFunc = (playerUpdateFunc)((uintptr_t)(gameAddr + 0x6EA60));
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)ogFunc, playerUpdateHook);
    DetourTransactionCommit();

    //get the gamestate//
    StateManager* stateManager = **reinterpret_cast<StateManager***>((uintptr_t)(gameAddr + 0x1A6E58));
    GameState* t = reinterpret_cast<GameState*>(stateManager->getState(0));
    
    t->player.inventoryGUI.craftingText.text = "Baka Mod"; //replace the crafting text
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        hMod = hModule;
        HANDLE thread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, NULL, NULL, NULL);
    }
    return TRUE;
}

