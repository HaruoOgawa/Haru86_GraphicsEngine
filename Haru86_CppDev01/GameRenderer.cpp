#include "GameRenderer.h"
#include "GL/glew.h"
#include "GameObject.h"
#include "MeshRendererComponent.h"
#include "TransformComponent.h"
#include "./Game.h"
#include "./Texture.h"

GameRenderer* GameRenderer::renderer_instance = nullptr;

void GameRenderer::Create() {
	if (!renderer_instance) {
		renderer_instance = new GameRenderer(Game::GetInstance());
	}
}

void GameRenderer::Destroy() {
	delete renderer_instance;
	renderer_instance = nullptr;
}

GameRenderer::GameRenderer(Game* game)
	: mgame(game),
	sWindow(nullptr),
	sWindowWidth(500),
	sWindowHeight(500),
	deltaTime(0.0f)
{

}

GameRenderer::~GameRenderer() {

}

bool GameRenderer::Initialize(float width,float height) {
	//sWindowWidth = width;
	//sWindowHeight = height;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,1);

	sWindow = SDL_CreateWindow(
		"Haru86_GLVJ",
		100,
		100,
		static_cast<int>(sWindowWidth),
		static_cast<int>(sWindowHeight),
		SDL_WINDOW_OPENGL
	);

	if (!sWindow) {
		SDL_Log("Failure! Can not initialize SDL_OpenGL Window: %s", SDL_GetError());
		return false;
	}
	
	if (SDL_SetWindowFullscreen(sWindow, SDL_WINDOW_FULLSCREEN_DESKTOP)!=0) {
		SDL_Log("Full Screeen Error: %s", SDL_GetError());
	}

	SDL_GetWindowSize(sWindow, &sWindowWidth, &sWindowHeight);
	
	context = SDL_GL_CreateContext(sWindow);

	glewExperimental = GL_TRUE;
	const GLenum error = glewInit();
	if (error != GLEW_OK) {
		SDL_Log("Failure! Can not initialize Glew: %s",glewGetErrorString(error));
		return false;
	}
	glGetError();

	if (!CreateFrameBuffer()) {
		SDL_Log("Can not create frame buffer");
	}

	return true;
}

glm::ivec2 GameRenderer::GetScreenSize() {
	return glm::ivec2(sWindowWidth, sWindowHeight);
}

bool GameRenderer::CreateFrameBuffer() {
	int width = static_cast<int>(GetScreenSize().x*0.5) ;
	int height = static_cast<int>(GetScreenSize().y*0.5) ;
	frameTexture =new Texture();

	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	frameTexture = new Texture();
	frameTexture->CreateForRendering(width, height, GL_RGB);

	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, frameTexture->GetTextureID(), 0);

	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		glDeleteFramebuffers(1, &frameBuffer);
		frameTexture->Unload();
		delete frameTexture;
		frameTexture = nullptr;
		return false;
	}
	return true;

}

void GameRenderer::Draw() {
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glViewport(0, 0, GetScreenSize().x, GetScreenSize().y);
	
	glClearColor(0.0f, 0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	for (auto obj : mgame->gameObjectList) {
		obj->transform->CalMatrix();
		obj->meshComp->Draw();
	}

	glFlush();

	//pass2////////////////////////////////////////////////
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, GetScreenSize().x , GetScreenSize().y);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	
	for (auto obj : mgame->boardGameObjectList) {
		obj->transform->CalMatrix();
		frameTexture->SetActive(0);
		obj->meshComp->material->SetTexUniform("frameTex", 0);
		obj->meshComp->DrawBoard();
	}

	glFlush();

	SDL_GL_SwapWindow(sWindow);
}

void GameRenderer::ShutDown() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(sWindow);

	glDeleteFramebuffers(1, &frameBuffer);
	frameTexture->Unload();
	delete frameTexture;
	frameTexture = nullptr;
}
