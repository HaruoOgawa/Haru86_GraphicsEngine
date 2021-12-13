#pragma once
//#include "GL/glew.h"
#include "SDL.h"
#include "../Game/Game.h"
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
	bool CreateFrameBuffer(class Texture* fTex,unsigned int& fBuffer);
	glm::ivec2 GetScreenSize();
	float deltaTime;
	float frameResolusion;
	class Font* font;
	class Texture* frameTexture;
private:
	SDL_Window* sWindow;
	int sWindowWidth;
	int sWindowHeight;
	class Game* mgame;
	SDL_GLContext context;
	
	unsigned int frameBuffer;
	class Texture* postProcessTexture;
	unsigned int postProcessBuffer;
	
protected:
	static GameRenderer* renderer_instance;
};

