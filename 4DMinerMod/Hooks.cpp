#include "Hooks.hpp"

#include <Windows.h>
#include <detours.h>
#include "Modding.hpp"
#include "EventDispatcher.hpp"

#include "World.hpp"
#include "Player.hpp"

EventDispatcher* d;

typedef void(__fastcall* playerUpdateFunc)(Player* thiz, void* window, World* world);
playerUpdateFunc playerUpdate;

void __fastcall playerUpdateHook(Player* p, void* window, World* world) {
    d->fireEvent(EVENT_PRE_PLAYER_UPDATE, { (void*)p, (void*)window, (void*)world });
    playerUpdate(p, window, world);
    d->fireEvent(EVENT_POST_PLAYER_UPDATE, { (void*)p, (void*)window, (void*)world });
}

void Hooks::init(Modding* modding) {
    d = modding->getDispatcher();

    //setup real functions vars//
    playerUpdate = (playerUpdateFunc)((uintptr_t)(modding->getGameAddress() + 0x6EA60));

    //hooks//
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    {
        DetourAttach(&(PVOID&)playerUpdate, playerUpdateHook);
    }
    DetourTransactionCommit();
}