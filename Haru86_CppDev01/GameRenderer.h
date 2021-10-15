#pragma once
//#include "GL/glew.h"
#include "SDL.h"
#include "./Game.h"

class GameRenderer
{
public:
	GameRenderer(class Game* game);
	~GameRenderer();
	bool Initialize(float width, float height);
	void ShutDown();
	void Draw();
	float deltaTime;
private:
	SDL_Window* sWindow;
	float sWindowWidth;
	float sWindowHeight;
	class Game* mgame;
	SDL_GLContext context;
};

