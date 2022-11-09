#pragma once

class State;

class StateManager {
public:
	//get state in levels hierarchy, for example in CreateWorld menu the 0 state is the TitleState, 1 state is SinglePlayerState and 2 state is CreateWorldState//
	State* getState(int level);
};