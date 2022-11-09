#include "Events.hpp"

IEvent::IEvent(Events e_, bool cancelled_) {
	this->e = e_;
	this->cancelled = cancelled_;
}

PlayerUpdateEvent::PlayerUpdateEvent(bool pre, Player* p, void* wi, World* w) {
	this->e = EVENT_PLAYER_UPDATE;
	this->isPre = pre;
	this->player = p;
	this->window = wi;
	this->world = w;
}

BlockBreakEvent::BlockBreakEvent(ToolItem* i, class Player* p, class World* w, uint8_t blockId) {
	this->e = EVENT_BLOCK_BREAK;
	this->item = i;
	this->player = p;
	this->world = w;
	this->blockId = blockId;
}

PlayerCollisionEvent::PlayerCollisionEvent(Player* p, World* w) {
	this->e = EVENT_PLAYER_COLLISION;
	this->player = p;
	this->world = w;
}

PlayerKeyInputEvent::PlayerKeyInputEvent(class Player* p, void* w, int k, int s, int a, char m) {
	this->e = EVENT_PLAYER_KEY_INPUT;
	this->player = p;
	this->window = w;
	this->key = k;
	this->scancode = s;
	this->action = a;
	this->mods = m;
}