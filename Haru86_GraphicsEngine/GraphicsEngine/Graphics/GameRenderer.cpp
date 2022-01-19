#include "GameRenderer.h"
#include "GL/glew.h"
#include "../Object/GameObject.h"
#include "../Component/MeshRendererComponent.h"
#include "../Component/TransformComponent.h"
#include "../Game/Game.h"
#include "./Texture.h"
#include "./Font.h"
#include "GraphicsEngine/App/BaseApp/BaseApp.h"
#include "GraphicsEngine/Object/RaymarchingObject.h"
#include "GraphicsEngine/Graphics/PolygonRaymarchingMixer.h"
#include "GraphicsEngine/Graphics/PostProcess.h"

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
	deltaTime(0.0f),
	frameResolusion(0.7),
	font(nullptr),
	polygon_frameTexture(std::make_shared<Texture>()),
	polygon_depthTexture(std::make_shared<Texture>()),
	raymarching_frameTexture(std::make_shared<Texture>()),
	raymarching_depthTexture(std::make_shared<Texture>()),
	p_r_BlendingTexture(std::make_shared<Texture>()),
	m_PolygonPostProcess_FrameTexture(std::make_shared<Texture>()),
	m_LatePostProcess_FrameTexture(std::make_shared<Texture>())
{
	PostProcess::CreateInstance();
}

GameRenderer::~GameRenderer() {

}

bool GameRenderer::Initialize(float width,float height) {
	
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

	//CreateFrameBuffer
	if (!CreateFrameBuffer(polygon_frameTexture, polygon_frameBuffer,GL_RGBA, GL_RGBA)) {
		SDL_Log("Can not create frame buffer");
	}
	
	if (!CreateFrameBuffer(polygon_depthTexture, polygon_depthBuffer,GL_RGBA, GL_RGBA)) {
		SDL_Log("Can not create frame buffer");
	}

	if (!CreateFrameBuffer(raymarching_frameTexture, raymarching_frameBuffer, GL_RGBA, GL_RGBA)) {
		SDL_Log("Can not create frame buffer");
	}

	if (!CreateFrameBuffer(raymarching_depthTexture, raymarching_depthBuffer, GL_RGBA, GL_RGBA)) {
		SDL_Log("Can not create frame buffer");
	}
	
	if (!CreateFrameBuffer(p_r_BlendingTexture, p_r_BlendingBuffer, GL_RGBA, GL_RGBA)) {
		SDL_Log("Can not create frame buffer");
	}
	
	if (!CreateFrameBuffer(m_PolygonPostProcess_FrameTexture, m_PolygonPostProcess_FrameBuffer, GL_RGBA, GL_RGBA)) {
		SDL_Log("Can not create frame buffer");
	}
	
	if (!CreateFrameBuffer(m_LatePostProcess_FrameTexture, m_LatePostProcess_FrameBuffer, GL_RGBA, GL_RGBA)) {
		SDL_Log("Can not create frame buffer");
	}

	font =  std::make_shared<Font>();
	if (!(font->Load("./Assets/Resources/FontData/FRSCRIPT.TTF"))) {
		font.reset();
		font == nullptr;
	}

	m_Mixer = std::make_unique<PolygonRaymarchingMixer>();

	return true;
}

glm::ivec2 GameRenderer::GetScreenSize() {
	return glm::ivec2(sWindowWidth, sWindowHeight);
}

bool GameRenderer::CreateFrameBuffer(std::shared_ptr<Texture> fTex, unsigned int& fBuffer, GLint internalformat, GLint format) {
	int width = static_cast<int>(GetScreenSize().x) ;
	int height = static_cast<int>(GetScreenSize().y );
	
	glGenFramebuffers(1, &fBuffer);
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);

	fTex->CreateForRendering(width, height,internalformat, format);
	
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);

	glBindFramebuffer(GL_FRAMEBUFFER, fBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fTex->GetTextureID(), 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;

}

void GameRenderer::Draw() {
	//ポリゴンオブジェクトのカラーマップをレンダリング///////////////////
	Game::GetInstance()->renderingTarget = ERerderingTarget::COLOR;
	glBindFramebuffer(GL_FRAMEBUFFER, polygon_frameBuffer);
	glViewport(0, 0, static_cast<int>(GetScreenSize().x * frameResolusion), static_cast<int>(GetScreenSize().y * frameResolusion));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	for (auto obj : mgame->gameObjectList) {
		obj->transform->CalMatrix();
		obj->meshComp->Draw();
	}

	if (mgame->app) {
		mgame->app->Draw();
	}

	//ポリゴンオブジェクトをデプスマップをレンダリング
	Game::GetInstance()->renderingTarget = ERerderingTarget::DEPTH;
	glBindFramebuffer(GL_FRAMEBUFFER, polygon_depthBuffer);
	glViewport(0, 0, static_cast<int>(GetScreenSize().x * frameResolusion), static_cast<int>(GetScreenSize().y * frameResolusion));

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	for (auto obj : mgame->gameObjectList) {
		obj->transform->CalMatrix();
		obj->meshComp->Draw();
	}

	if (mgame->app) {
		mgame->app->Draw();
	}

	// ポリゴンオブジェクトのポストプロセス
	PostProcess::GetInstance()->DrawPolygonPostProcess(polygon_frameTexture, m_PolygonPostProcess_FrameBuffer);

	//レイマーチングオブジェクトのカラーマップをレンダリング///////////////
	if (Game::GetInstance()->m_RaymarchingObject) {
		Game::GetInstance()->renderingTarget = ERerderingTarget::COLOR;
		glBindFramebuffer(GL_FRAMEBUFFER, raymarching_frameBuffer);
		glViewport(0, 0, static_cast<int>(GetScreenSize().x * frameResolusion), static_cast<int>(GetScreenSize().y * frameResolusion));

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		Game::GetInstance()->m_RaymarchingObject->transform->CalMatrix();
		Game::GetInstance()->m_RaymarchingObject->Draw();
	}

	//レイマーチングオブジェクトのデプスマップをレンダリング
	if (Game::GetInstance()->m_RaymarchingObject) {
		Game::GetInstance()->renderingTarget = ERerderingTarget::DEPTH;
		glBindFramebuffer(GL_FRAMEBUFFER, raymarching_depthBuffer);
		glViewport(0, 0, static_cast<int>(GetScreenSize().x * frameResolusion), static_cast<int>(GetScreenSize().y * frameResolusion));

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		Game::GetInstance()->m_RaymarchingObject->transform->CalMatrix();
		Game::GetInstance()->m_RaymarchingObject->Draw();
	}

	//ポリゴンオブジェクトとレイマーチングオブジェクトをブレンドする
	Game::GetInstance()->renderingTarget = ERerderingTarget::COLOR;
	glBindFramebuffer(GL_FRAMEBUFFER, p_r_BlendingBuffer);
	glViewport(0, 0, static_cast<int>(GetScreenSize().x * frameResolusion), static_cast<int>(GetScreenSize().y * frameResolusion));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	//ミキシング
	m_Mixer->Draw();

	//ミキシングしたフレームバッファのポストプロセス////////////////////////////////////////
	// ポストプロセスオブジェクトを作り、それにTextureのshared_ptrを渡して任意のタイミングで関数を呼ぶことでポストプロセスを実現
	// 	   ブレンド前にポリゴンに適応するもの(Bloom・Glowなど)やブレンド後に全体に適応するもの(Vignet・Noiseなど)もあるはずだから
	//ポストプロセスオブジェクトなるものを作ってもいいかもしれない
	//よく使うものはプリセットとして用意しておいて使いたいもののブーリアンをtrueにして使用
	//複数のポストプロセスはカラーブレンドする
	//カスタムポストプロセスもここで宣言する
	PostProcess::GetInstance()->DrawLatePostProcess(p_r_BlendingTexture, m_LatePostProcess_FrameBuffer);

	//最終的な結果を作成する///////////////////////////////
	Game::GetInstance()->renderingTarget = ERerderingTarget::COLOR;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, GetScreenSize().x, GetScreenSize().y);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

	for (auto obj : mgame->boardGameObjectList) {
		obj->transform->CalMatrix();
		obj->meshComp->DrawBoard();
	}

	//垂直同期を実行
	SDL_GL_SwapWindow(sWindow);
}

void GameRenderer::ShutDown() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(sWindow);

	PostProcess::DestroyInstance();
	
	if (polygon_frameTexture!=nullptr) {
		glDeleteFramebuffers(1, &polygon_frameBuffer);
		polygon_frameTexture->Unload();
		polygon_frameTexture.reset();
		polygon_frameTexture = nullptr;
	}

	if (polygon_depthTexture != nullptr) {
		glDeleteFramebuffers(1, &polygon_depthBuffer);
		polygon_depthTexture->Unload();
		polygon_depthTexture.reset();
		polygon_depthTexture = nullptr;
	}

	if (raymarching_frameTexture != nullptr) {
		glDeleteFramebuffers(1, &raymarching_frameBuffer);
		raymarching_frameTexture->Unload();
		raymarching_frameTexture.reset();
		raymarching_frameTexture = nullptr;
	}

	if (raymarching_depthTexture != nullptr) {
		glDeleteFramebuffers(1, &raymarching_depthBuffer);
		raymarching_depthTexture->Unload();
		raymarching_depthTexture.reset();
		raymarching_depthTexture = nullptr;
	}
}
