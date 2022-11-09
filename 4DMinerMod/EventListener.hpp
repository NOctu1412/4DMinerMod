#pragma once

#include "Events.hpp"

#include <vector>

class Listener {
public:
	std::vector<Events> listenTo; //list of events that the listener will listen

	void addEvent(Events e);
	void removeEvent(Events e);
	bool isListeningTo(Events e);

	virtual void listen(Events e, std::vector<void*> args);
};