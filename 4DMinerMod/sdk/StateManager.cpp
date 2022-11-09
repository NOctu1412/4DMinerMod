#include "StateManager.hpp"

#include <cstdint>

State* StateManager::getState(int level) {
	return *reinterpret_cast<State**>((uintptr_t)(this + level*sizeof(State*)));
}