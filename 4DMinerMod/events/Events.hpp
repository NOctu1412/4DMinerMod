#pragma once

enum Events {
	EVENT_PRE_PLAYER_UPDATE,
	EVENT_POST_PLAYER_UPDATE,
};

struct sEVENT_PRE_PLAYER_UPDATE {
	const class Player* player;
	const void* window;
	const class World* world;
};

struct sEVENT_POST_PLAYER_UPDATE {
	const class Player* player;
	const void* window;
	const class World* world;
};