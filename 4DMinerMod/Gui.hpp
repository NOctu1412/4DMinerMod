#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include "QuadRenderer.hpp"
#include "FontRenderer.hpp"

enum AlignmentX : int {
	ALIGN_LEFT = 0,
	ALIGN_RIGHT = 1,
	ALIGN_CENTER_X = 2
};

enum AlignmentY : int {
	ALIGN_TOP = 0,
	ALIGN_BOTTOM = 1,
	ALIGN_CENTER_Y = 2
};

class Element {
public:
	virtual void offsetY(int offset){}
	virtual void alignY(AlignmentY a){}
	virtual void offsetX(int offset){}
	virtual void alignX(AlignmentX a) {}
	virtual void getPos(class Window* w, int* x, int* y) {}
	virtual void getSize(class Window* w, int* width, int* height) {}
	virtual void fuk1() {}
	virtual bool fuk2() { return 0; }
	virtual bool fuk3() { return 0; }
	virtual bool fuk4() { return 0; }
	virtual bool fuk5() { return 0; }
	virtual bool fuk6() { return 0; }
	virtual bool fuk7() { return 0; }
	virtual void fuk8() {}
	virtual void fuk9() {}
};


class Text : public Element {
public:
	std::string text;
	int32_t xOffset, yOffset;
	AlignmentX xAlign;
	AlignmentY yAlign;
	glm::f32vec4 color;
	int32_t size, wrapWidth;
	bool shadow, fancy;
private:
	char uk1[6];
};

class CraftableRecipe {
public:

};

class CraftingMenu : public Element {
public:
	class Interface* interfacee;
	class InventoryCursor* cursor;
	std::vector<CraftableRecipe> craftableRecipes;
	int32_t xOffset, yOffset, xAlign, yAlign;
};

class Button : public Element {
public:
	std::string text;
	bool clickable, mouseDown, selected;
private:
	char uk1;
public:
	int32_t xOffset, yOffset;
	AlignmentX xAlign;
	AlignmentY yAlign;
	int32_t width, height;
private:
	int uk2;
public:
	class State* user;
	void* callback;
};

class ElemContainer {
public:
	virtual void addElement(class Element* e);
	virtual bool removeElement(class Element* e);
	virtual bool selectElement(class Element* e);
	virtual void clear();
	virtual bool empty();
};

class Window {
public:
	virtual QuadRenderer* getQuadRenderer();
	virtual FontRenderer* getFontRenderer();
	virtual void* getGLFWwindow();
	virtual void getCursorPos(int* x, int* y);
	virtual void getSize(int* x, int* y);
	virtual void changeViewport(const glm::i32vec4* pos, glm::i32vec2* scroll);
};

class Interface : public Window, public ElemContainer {
public:
	std::vector<Element*> elements;
	int32_t selectedElemIndex;
private:
	int uk1;
public:
	QuadRenderer* qr;
	FontRenderer* font;
	void* window, *viewportCallback, *viewportUser;
	char viewUpdateFlag;
private:
	char uk2[7];
};

class ContentBox : public Window, public Element, public ElemContainer {
public:
	Element* parent;
	std::vector<Element*> elements;
	int32_t selectedItemIndex;
	bool active;
private:
	char uk1[3];
public:
	int32_t width, height, xOffset, yOffset, xAlign, xScroll, yAlign, yScroll, scrollW, scrollH;
	bool scrollingX, scrollingY;
private:
	short uk2;
public:
	int32_t scrollbarClickPos, scrollStep;
	char viewUpdateFlag;
private:
	char uk3[3];
};