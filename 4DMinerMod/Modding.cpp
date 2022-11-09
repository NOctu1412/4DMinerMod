#include "Modding.hpp"

#include <Windows.h>

#include "helpers.hpp"
#include "StateManager.hpp"
#include "EventDispatcher.hpp"
#include "Hooks.hpp"

Modding* modding;

Hooks* hooks;
EventDispatcher* dispatcher;
StateManager* stateManager;

uintptr_t gameAddr;
uintptr_t stateManagerOffset = 0x1A6E58;

Modding::Modding() {
	modding = this;
	init();
}

Modding* Modding::getInstance() {
	return modding;
}

void Modding::init() {
	OpenConsole();
	gameAddr = (uintptr_t)GetModuleHandleA("4D Miner.exe");
	hooks = new Hooks();
	dispatcher = new EventDispatcher();
	stateManager = **reinterpret_cast<StateManager***>((uintptr_t)(gameAddr + stateManagerOffset));

	hooks->init(modding);
}

Hooks* Modding::getHooks() {
	return hooks;
}

EventDispatcher* Modding::getDispatcher() {
	return dispatcher;
}

StateManager* Modding::getStateManager() {
	return stateManager;
}

uintptr_t Modding::getGameAddress(){
	return gameAddr;
}
