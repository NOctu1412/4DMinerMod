#pragma once

#include "FontRenderer.hpp"
#include "QuadRenderer.hpp"
#include "TexRenderer.hpp"
#include "MeshRenderer.hpp"
#include "World.hpp"
#include "Player.hpp"

class StateManager;

class State {
};

class TitleState : public State {
public:
	glm::fmat4x4 projection2D;
	glm::fmat4x4 projection3D;
	int32_t displayProgress;
	char uk1, uk2, uk3, uk4;
	FontRenderer font;
	QuadRenderer qr;
	int64_t qs;
	TexRenderer logoRenderer;
	int32_t rotation;
	char uk5, uk6, uk7, uk8;
	//not finished

	virtual void init(StateManager* s);
	virtual void close(StateManager* s);
	virtual void update(StateManager* s);
	virtual void render(StateManager* s);
	virtual void fuk1();
	virtual void resume(StateManager* s);
	virtual void mouseInput(StateManager* s, double mouseX, double mouseY);
	virtual void fuk2();
	virtual void mouseButtonInput(StateManager* s, int button, int action, int mode);
	virtual void keyInput(StateManager* s, int key, int scancode, int action, int mods);
	virtual void fuk3();
};

class GameState : public State {
public:
	World world;
	CloudManager clouds;
	glm::fmat4x4 projection2D;
	glm::fmat4x4 projection3D;
	int64_t cloudShader;
	int32_t cloudmvID, cloudBlendID, cloudTexID;
private:
	int uk1;
public:
	int64_t levelShader;
	int32_t levelShaderTexID;
	int32_t levelShadermvID;
	MeshRenderer blockRenderer, skyboxRenderer;
	int64_t moonShader, moonTex;
	int32_t moonTexID, moonmvID, moonBlendID;
private:
	int uk2;
public:
	MeshRenderer moonRenderer;
	int64_t tex2DShader;
	TexRenderer crosshairRenderer;
	int64_t blockShader, targetBlockShader;
private:
	int uk3;
public:
	Player player;
	glm::dvec2 initialCursorPos;
	int32_t renderDistance, cloudRenderDistance, FOV;
private:
	int uk4;
public:

	virtual void update(StateManager* s);
	virtual void close(StateManager* s);
	virtual void render(StateManager* s);
	virtual void pause(StateManager* s);
	virtual void resume(StateManager* s);
	virtual void mouseInput(StateManager* s, double mouseX, double mouseY);
	virtual void scroilInput(StateManager* s, double mouseX, double mouseY);
	virtual void mouseButtonInput(StateManager* s, int button, int action, int mode);
	virtual void keyInput(StateManager* s, int key, int scancode, int action, int mods);
	virtual void windowResize(StateManager* s, int width, int height);
	virtual void fuk1();
};