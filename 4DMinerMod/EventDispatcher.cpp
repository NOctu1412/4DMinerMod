#include "EventDispatcher.hpp"

void EventDispatcher::addListener(Listener* listener) {
	for(auto e : listener->listenTo) {
		if(!std::count(this->listeners[e].begin(), this->listeners[e].end(), listener))
			this->listeners[e].push_back(listener);
	}
}

void EventDispatcher::removeListener(Listener* listener) {
	/*for (auto e : listener->listenTo) {
		if (std::count(this->listeners[e].begin(), this->listeners[e].end(), listener))
			this->listeners.erase(std::remove(this->listeners.begin(), this->listeners.end(), listener), this->listeners.end());
	}*/
}

void EventDispatcher::subListenerTo(Listener* listener, Events e) {
	listener->addEvent(e);
	this->listeners[e].push_back(listener);
}

std::vector<Listener*> EventDispatcher::getListenersThatListenTo(Events e){
	if (this->listeners.find(e) != this->listeners.end())
		return this->listeners[e];
	return std::vector<Listener*>();
}

void EventDispatcher::fireEvent(Events e, std::vector<void*> args) {
	if (this->listeners.find(e) != this->listeners.end()) {
		for (auto& l : this->listeners[e]) {
			l->listen(e, args);
		}
	}
}