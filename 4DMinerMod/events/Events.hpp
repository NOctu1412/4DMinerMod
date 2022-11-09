#pragma once

#include <cstdint>

enum Events {
	EVENT_NONE, //no event
	EVENT_PLAYER_UPDATE,
	EVENT_PLAYER_COLLISION,
	EVENT_PLAYER_KEY_INPUT,
	EVENT_BLOCK_BREAK,
};

class IEvent {
public:
	Events e = EVENT_NONE;
	bool cancelled = false;
	bool modified = false;

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

class PlayerCollisionEvent : public IEvent {
public:
	class Player* player = nullptr;
	class World* world = nullptr;

	PlayerCollisionEvent(class Player* p, class World* w);
};

class PlayerKeyInputEvent : public IEvent {
public:
	class Player* player = nullptr;
	void* window = nullptr;
	int key = -1, scancode = -1, action = -1;
	char mods = 0;

	PlayerKeyInputEvent(class Player* p, void* w, int k, int s, int a, char m);
};

class BlockBreakEvent : public IEvent {
public:
	class ToolItem* item = nullptr;
	class Player* player = nullptr;
	class World* world = nullptr;
	uint8_t blockId = 0;

	BlockBreakEvent(ToolItem* i, class Player* p, class World* w, uint8_t blockId);
};