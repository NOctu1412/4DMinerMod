#include "Modding.hpp"

#include <Windows.h>

#include "helpers.hpp"
#include "Hooks.hpp"
#include <eventpp/eventdispatcher.h>
#include "events/Events.hpp"

Modding* modding;

Hooks* hooks;
eventpp::EventDispatcher<Events, void(std::vector<void*>)> dispatcher;
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
	stateManager = **reinterpret_cast<StateManager***>((uintptr_t)(gameAddr + stateManagerOffset));
	hooks->init(modding);
}

Hooks* Modding::getHooks() {
	return hooks;
}

void* Modding::getDispatcher() {
	return &dispatcher;
}

StateManager* Modding::getStateManager() {
	if(stateManager == nullptr)
		stateManager = **reinterpret_cast<StateManager***>((uintptr_t)(gameAddr + stateManagerOffset));
	return stateManager;
}

uintptr_t Modding::getGameAddress(){
	return gameAddr;
}
