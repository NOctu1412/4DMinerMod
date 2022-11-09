#include <Windows.h>
#include <iostream>

#include "Modding.hpp"
#include "EventDispatcher.hpp"

#include "Player.hpp"

/*void __fastcall playerUpdateHook(Player* p, void* window, World* world) {
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

    ogFunc(p, window, world);
}*/

class TestListener : public Listener {
public:
    TestListener() {
        this->addEvent(EVENT_PRE_PLAYER_UPDATE);
        this->addEvent(EVENT_POST_PLAYER_UPDATE);
    }

    void listen(Events e, std::vector<void*> args) override {
        if (e == EVENT_PRE_PLAYER_UPDATE) {
            if (((Player*)args[0])->targetingBlock && ((Player*)args[0])->keys.leftMouseDown) {
                ((Player*)args[0])->targetDamage = 1.0;
            }
        }
    }
};

void MainThread() {
    Modding* modding = new Modding();
    modding->getDispatcher()->addListener(new TestListener());
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

