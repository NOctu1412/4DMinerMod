#define NOMINMAX

#include <Windows.h>
#include <iostream>

#include "Modding.hpp"
#include "events/Events.hpp"
#include <eventpp/eventdispatcher.h>

#include "sdk/Player.hpp"

void MainThread() {
    Modding* modding = new Modding();
    auto d = (eventpp::EventDispatcher<Events, void(std::vector<void*>)>*) modding->getDispatcher();

    d->appendListener(EVENT_PRE_PLAYER_UPDATE, [](std::vector<void*> args) {
        if (((Player*)args[0])->targetingBlock && ((Player*)args[0])->keys.leftMouseDown) {
            ((Player*)args[0])->targetDamage = 1.0;
        }
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

