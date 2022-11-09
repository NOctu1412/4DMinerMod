#include "Hooks.hpp"

#include <Windows.h>
#include <iostream>
#include <detours.h>
#include "Modding.hpp"

#include <eventpp/eventdispatcher.h>
#include "events/Events.hpp"

#include "sdk/World.hpp"
#include "sdk/Player.hpp"

eventpp::EventDispatcher<Events, void(std::vector<void*>)>* d;

typedef void(__fastcall* playerUpdateFunc)(Player* thiz, void* window, World* world);
playerUpdateFunc playerUpdate;

void __fastcall playerUpdateHook(Player* p, void* window, World* world) {
    d->dispatch(EVENT_PRE_PLAYER_UPDATE, { (void*)p, window, (void*)world });
    playerUpdate(p, window, world);
    d->dispatch(EVENT_POST_PLAYER_UPDATE, { (void*)p, window, (void*)world });
}

void Hooks::init(Modding* modding) {
    d = (eventpp::EventDispatcher<Events, void(std::vector<void*>)>*) modding->getDispatcher();

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