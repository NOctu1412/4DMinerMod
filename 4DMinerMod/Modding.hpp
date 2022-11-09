#pragma once

#include <cstdint>

class Modding {
public:
	Modding();
	static Modding* getInstance();

private:
	void init();
public:
	class Hooks* getHooks();
	void* getDispatcher();
	class StateManager* getStateManager();
	uintptr_t getGameAddress();
};