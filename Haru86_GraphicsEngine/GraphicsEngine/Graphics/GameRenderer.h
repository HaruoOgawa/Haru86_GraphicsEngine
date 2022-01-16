#pragma once
#include "SDL.h"
#include "../Game/Game.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <memory>

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
	bool CreateFrameBuffer(std::shared_ptr<class Texture> fTex,unsigned int& fBuffer, GLint internalformat, GLint format);
	glm::ivec2 GetScreenSize();
	float deltaTime;
	float frameResolusion;
	std::shared_ptr<class Font> font;
	std::shared_ptr<class Texture> frameTexture;
private:
	SDL_Window* sWindow;
	int sWindowWidth;
	int sWindowHeight;
	class Game* mgame;
	SDL_GLContext context;
	
	unsigned int frameBuffer;
	std::shared_ptr<class Texture> postProcessTexture;
	unsigned int postProcessBuffer;
	
protected:
	static GameRenderer* renderer_instance;
};

