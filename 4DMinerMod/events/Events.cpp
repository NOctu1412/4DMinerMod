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