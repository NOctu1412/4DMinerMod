#include "EventListener.hpp"

void Listener::addEvent(Events e) {
	if (!isListeningTo(e))
		this->listenTo.push_back(e);
}

/*void Listener::removeEvent(Events e) {
	if (isListeningTo(e))
		this->listenTo.erase(std::remove(this->listenTo.begin(), this->listenTo.end(), e), this->listenTo.end());
}*/

bool Listener::isListeningTo(Events e) {
	return std::count(this->listenTo.begin(), this->listenTo.end(), e);
}

void Listener::listen(Events e, std::vector<void*> args) {}