#pragma once

#include <cstdint>

enum Events {
	EVENT_NONE, //no event
	EVENT_PLAYER_UPDATE,
	EVENT_BLOCK_BREAK
};

class IEvent {
public:
	Events e = EVENT_NONE;
	bool cancelled = false;

	IEvent() {};
	IEvent(Events e_, bool cancelled_);
};

class PlayerUpdateEvent : public IEvent {
public:
	bool isPre = false;
	class Player* player = nullptr;
	void* window = nullptr;
	class World* world = nullptr;

	PlayerUpdateEvent(bool pre, class Player* p, void* wi, class World* w);
};

class BlockBreakEvent : public IEvent {
public:
	class ToolItem* item = nullptr;
	class Player* player = nullptr;
	class World* world = nullptr;
	uint8_t blockId = 0;

	BlockBreakEvent(ToolItem* i, class Player* p, class World* w, uint8_t blockId);
};