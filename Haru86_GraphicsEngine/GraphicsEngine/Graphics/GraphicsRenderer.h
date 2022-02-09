#pragma once
#include "SDL.h"
#include "../Game/Game.h"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <memory>

class GraphicsRenderer
{
public:
	static GraphicsRenderer* GetInstance() {
		return renderer_instance;
	}
	static void Create();
	static void Destroy();

	GraphicsRenderer(class Game* game);
	~GraphicsRenderer();
	bool Initialize(float width, float height);
	void ShutDown();
	void Draw();
	bool CreateFrameBuffer(std::shared_ptr<class Texture> fTex,unsigned int& fBuffer, GLint internalformat, GLint format, GLenum type = GL_UNSIGNED_BYTE);
	glm::ivec2 GetScreenSize();
	float deltaTime;
	float frameResolusion;
	std::shared_ptr<class Font> font;

	//FrameTextures
	std::shared_ptr<class Texture> polygon_frameTexture;
	std::shared_ptr<class Texture> polygon_depthTexture;
	std::shared_ptr<class Texture> raymarching_frameTexture;
	std::shared_ptr<class Texture> raymarching_depthTexture;
	std::shared_ptr<class Texture> p_r_BlendingTexture;
	//PostProcess FrameTexture
	std::shared_ptr<class Texture> m_PolygonPostProcess_FrameTexture;
	std::shared_ptr<class Texture> m_LatePostProcess_FrameTexture;

	void SetBackgroundColor(glm::vec3 color);
	
	friend class PolygonRaymarchingMixer;
private:
	SDL_Window* sWindow;
	int sWindowWidth;
	int sWindowHeight;
	class Game* mgame;
	SDL_GLContext context;
	
	//FrameBuffer
	unsigned int polygon_frameBuffer;
	unsigned int polygon_depthBuffer;
	unsigned int raymarching_frameBuffer;
	unsigned int raymarching_depthBuffer;
	unsigned int p_r_BlendingBuffer;
	//PostProcess FrameBuffer
	unsigned int m_PolygonPostProcess_FrameBuffer;
	unsigned int m_LatePostProcess_FrameBuffer;

	//ポリゴンとレイマーチングのミックス
	std::unique_ptr<class PolygonRaymarchingMixer> m_Mixer;
	
	// 初期化時の背景色
	glm::vec3 m_BackgroundColor;
protected:
	static GraphicsRenderer* renderer_instance;
};

