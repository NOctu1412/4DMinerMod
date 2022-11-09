#pragma once

#include <glm/glm.hpp>
#include <cstdint>

#include "Inventory.hpp"
#include "Mat.hpp"

class PlayerKeys {
public:
	bool w, a, s, d, x, z, q, e, space, shift, ctrl, leftMouseDown, rightMouseDown;
};

class Player {
public:
	PlayerKeys keys;
private:
	char uk1[3];
public:
	int32_t scrollFactor, lookSensivity;
	bool touchingGround, crouching, sprinting, walking;
	glm::f32vec4 pos;
	int32_t headPos;
	glm::f32vec4 cameraPos;
	int32_t walkAnimOffset, walkAnimTheta;
	glm::i32vec4 currentBlock;
	glm::f32vec4 lastChunkPos;
	int32_t hyperPlaneUpdateFlag;
private:
	char uk2[3];
public:
	glm::f32vec4 forward, up, right, over;
	Mat5 orientation;
	glm::f32vec4 vel;
private:
	char uk3[4];
public:
	int64_t mouseX, mouseY, walkStartTime, mouseDownTime, placeTime;
	glm::i32vec4 targetBlock;
	bool targetingBlock;
private:
	char uk4[7];
public:
	int64_t targetTime;
	float targetDamage;
	glm::i32vec4 targetPlaceBlock;
	bool canPlace;
private:
	char uk5[3];
public:
	glm::f32vec4 reachEndpoint;
	Inventory hotbar, inventory;
	PlayerInventoryManager playerInventory;
	InventoryGUI inventoryGUI;
	bool shouldThrowItem;
private:
	char uk6[7];
public:
	std::unique_ptr<Item> queudThrowItem;
	bool shouldResetMouse;
private:
	char uk7[3];
public:
	int32_t health;
	int64_t hitTime, damageTime;
	int32_t headBlock;
private:
	int uk8;
};