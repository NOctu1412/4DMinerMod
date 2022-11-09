#pragma once

#include <unordered_map>
#include "EventListener.hpp"

class EventDispatcher {
public:
	std::unordered_map<Events, std::vector<Listener*>> listeners;

	void addListener(Listener* listener);
	void removeListener(Listener* listener);
	void subListenerTo(Listener* listener, Events e);
	std::vector<Listener*> getListenersThatListenTo(Events e);

	void fireEvent(Events e, std::vector<void*> args);
};