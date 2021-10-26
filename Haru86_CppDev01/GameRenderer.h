#pragma once
//#include "GL/glew.h"
#include "SDL.h"
#include "./Game.h"
#include <glm/glm.hpp>

class GameRenderer
{
public:
	static GameRenderer* GetInstance() {
		return renderer_instance;
	}
	static void Create();
	static void Destroy();

	GameRenderer(class Game* game);
	~GameRenderer();
	bool Initialize(float width, float height);
	void ShutDown();
	void Draw();
	bool CreateFrameBuffer();
	glm::ivec2 GetScreenSize();
	float deltaTime;
private:
	SDL_Window* sWindow;
	int sWindowWidth;
	int sWindowHeight;
	class Game* mgame;
	SDL_GLContext context;
	class Texture* frameTexture;
	unsigned int frameBuffer;
protected:
	static GameRenderer* renderer_instance;
};

