#include "Hooks.hpp"


#include <Windows.h>
#include <iostream>
#include <detours.h>
#include "Modding.hpp"

#include "sdk/World.hpp"
#include "sdk/Player.hpp"

#include "events/Events.hpp"
#include <eventpp/eventdispatcher.h>

eventpp::EventDispatcher<Events, void(IEvent*)>* d;

typedef void(__fastcall* playerUpdateFunc)(Player* thiz, void* window, World* world);
playerUpdateFunc playerUpdate;

typedef void(__fastcall* playerCollisionFunc)(Player* thiz, World* world);
playerCollisionFunc playerCollision;

typedef bool(__fastcall* playerKeyInputFunc)(Player* thiz, void* w, int k, int s, int a, char m);
playerKeyInputFunc playerKeyInput;

typedef bool(__fastcall* blockBreakFunc)(ToolItem* thiz, World* world, Player* player, uint8_t blockId);
blockBreakFunc blockBreak;

void __fastcall playerUpdateHook(Player* p, void* window, World* world) {
    d->dispatch(EVENT_PLAYER_UPDATE, new PlayerUpdateEvent(true, p, window, world));
    playerUpdate(p, window, world);
    d->dispatch(EVENT_PLAYER_UPDATE, new PlayerUpdateEvent(false, p, window, world));
}

void __fastcall playerCollisionHook(Player* p, World* world) {
    IEvent* e = new PlayerCollisionEvent(p, world);
    d->dispatch(EVENT_PLAYER_COLLISION, e);
    if (e->cancelled)
        return;
    playerCollision(p, world);
}

bool __fastcall playerKeyInputHook(Player* thiz, void* w, int k, int s, int a, char m) {
    PlayerKeyInputEvent* e = new PlayerKeyInputEvent(thiz, w, k, s, a, m);
    d->dispatch(EVENT_PLAYER_KEY_INPUT, e);
    if (e->cancelled)
        return false;
    if (e->modified) {
        return playerKeyInput(thiz, w, e->key, e->scancode, e->action, e->mods);
    }
    return playerKeyInput(thiz, w, k, s, a, m);
}

bool blockBreakHook(ToolItem* thiz, World* world, Player* player, uint8_t blockId) {
    BlockBreakEvent* e = new BlockBreakEvent(thiz, player, world, blockId);
    d->dispatch(EVENT_BLOCK_BREAK, e);
    if (e->cancelled) {
        return false;
    }
    return blockBreak(thiz, world, player, blockId);
}

void Hooks::init(Modding* modding) {
    d = (eventpp::EventDispatcher<Events, void(IEvent*)>*) modding->getDispatcher();

    //setup real functions vars//
    playerUpdate = (playerUpdateFunc)((uintptr_t)(modding->getGameAddress() + 0x6EA60));
    playerCollision = (playerCollisionFunc)((uintptr_t)(modding->getGameAddress() + 0x6A560));
    playerKeyInput = (playerKeyInputFunc)((uintptr_t)(modding->getGameAddress() + 0x70BB0));
    blockBreak = (blockBreakFunc)((uintptr_t)(modding->getGameAddress() + 0x86B00));

    //hooks//
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    {
        DetourAttach(&(PVOID&)playerUpdate, playerUpdateHook);
        DetourAttach(&(PVOID&)playerCollision, playerCollisionHook);
        DetourAttach(&(PVOID&)playerKeyInput, playerKeyInputHook);
        DetourAttach(&(PVOID&)blockBreak, blockBreakHook);
    }
    DetourTransactionCommit();
}