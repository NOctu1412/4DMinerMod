#pragma once

#include <cstdint>
#include <glm/glm.hpp>

#include "Item.hpp"
#include "Gui.hpp"

class InventoryCursor {
public:
	std::unique_ptr<Item> item;
	glm::i32vec2 pos;
};

class InventoryIterator {
public:
	int64_t manager;
	int32_t index;
private:
	int uk1;
};

class InventoryManager {
public:
	virtual void render(glm::i32vec2* cursorPos);
	virtual bool addItem(std::unique_ptr<Item>* item);
	virtual bool mouseButtonEvent(InventoryManager* other, InventoryCursor* cursor, int button, int action, int mods);
	virtual InventoryIterator* begin(InventoryIterator* result);
	virtual InventoryIterator* end(InventoryIterator* result);
	virtual int64_t getSlotCount();
	virtual std::unique_ptr<Item>* getSlot(int index);
};

class Inventory : public InventoryManager {
public:
	glm::i32vec2 renderPos, size, selectedSlot;
	std::string label;
	std::vector<std::unique_ptr<Item>> slots;
};

class PlayerInventoryManager : public InventoryManager {
public:
	InventoryManager* hotbar, inventory;
};

class InventoryGUI {
public:
	InventoryManager* primary, second;
	InventoryCursor cursor;
	int32_t width, height;
	QuadRenderer qr;
	int64_t qs;
	Interface ui;
	Text craftingText;
	ContentBox craftingMenuBox;
	CraftingMenu craftingMenu;
};