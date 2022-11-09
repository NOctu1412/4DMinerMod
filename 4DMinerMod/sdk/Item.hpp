#pragma once

#include <cstdint>

#include "Mat.hpp"

class Item {
public:
	int32_t count;
private:
	int uk1;
public:

	virtual std::string* getName(std::string* result) { return nullptr; }
	virtual void renderEntity(const Mat5* MV, bool inHand){}
	virtual bool isDeadly() { return false; }
	virtual bool isCompatible(std::unique_ptr<Item>* other) { return false; }
	virtual int64_t getStackLimit() { return 0; }
	virtual bool action(class World* world, class Player* player, int action) { return false; }
	virtual bool breakBlock(class World* world, class Player* player, uint8_t blockId) { return false; }
	virtual bool entityAction(class World* world, class Player* player, std::unique_ptr<class Entity>*) { return false; }
	virtual std::unique_ptr<Item>* clone(std::unique_ptr<Item>* result) { return nullptr; }
	virtual void* saveAttributes(void* result) { return nullptr; }
};

class ToolItem : public Item {
public:
	std::string name;
};