#define NOMINMAX

#include <Windows.h>
#include <iostream>

#include "Modding.hpp"
#include "events/Events.hpp"
#include <eventpp/eventdispatcher.h>

#include "sdk/Player.hpp"

void MainThread() {
    Modding* modding = new Modding();
    auto d = (eventpp::EventDispatcher<Events, void(IEvent*)>*) modding->getDispatcher();

    d->appendListener(EVENT_PLAYER_UPDATE, [](IEvent* e) {
        PlayerUpdateEvent* event = (PlayerUpdateEvent*)e;
        if (event->player->targetingBlock && event->player->keys.leftMouseDown) {
            event->player->targetDamage = 1.0;
        }
    });
    
    d->appendListener(EVENT_BLOCK_BREAK, [](IEvent* e) {
        printf("Block broke !\n");
        e->cancelled = true;
    });
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        HANDLE thread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, NULL, NULL, NULL);
    }
    return TRUE;
}

