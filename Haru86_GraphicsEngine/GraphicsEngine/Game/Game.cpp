#include "Game.h"
#include <string>
#include "../Object/GameObject.h"
#include "../Graphics/Mesh.h"
#include "../Component/AudioSourceComponent.h"
#include "../Object/TimelineObject.h"
#include "../Component/TimelineComponent.h"
#include "./Time.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "../App/BaseApp/BaseApp.h"
#include "../../Assets/App/Kura02/Kura02.h"
//#include "../../Assets/App/KuraArtApp/KuraArtApp.h"
#include "../../Assets/App/DemoApp/DemoApp.h"


#include <exception>
#include <stdexcept>

Game* Game::s_pInstance = nullptr;

void Game::Create()
{
	if (!s_pInstance)
	{
		s_pInstance = new Game;
	}
}

void Game::Destroy()
{
	delete s_pInstance;
	s_pInstance = nullptr;
}

Game::Game()
	: 
	isRunning(true),
	time(0.0f),
	deltaTime(0.0f),
	previousTime(0.0f),
	mouseStateBool(false),
	animTime(0.0f),
	isRestart(false)
{
	
	for (int i = 0; i < 10;i++) {
		switch (i)
		{
		case 0:
			texSlots.emplace(i, GL_TEXTURE0);
			break;
		case 1:
			texSlots.emplace(i, GL_TEXTURE1);
			break;
		case 2:
			texSlots.emplace(i, GL_TEXTURE2);
			break;
		case 3:
			texSlots.emplace(i, GL_TEXTURE3);
			break;
		case 4:
			texSlots.emplace(i, GL_TEXTURE4);
			break;
		case 5:
			texSlots.emplace(i, GL_TEXTURE5);
			break;
		case 6:
			texSlots.emplace(i, GL_TEXTURE6);
			break;
		case 7:
			texSlots.emplace(i, GL_TEXTURE7);
			break;
		case 8:
			texSlots.emplace(i, GL_TEXTURE8);
			break;
		case 9:
			texSlots.emplace(i, GL_TEXTURE9);
			break;
		default:
			break;
		}
	}
}

Game::~Game() {
	
}

bool Game::Initialize() {
	if (SDL_Init(SDL_INIT_VIDEO||SDL_INIT_AUDIO)!=0) {
		SDL_Log("SDL Init is failure: %s", SDL_GetError());
		return false;
	}

	GameRenderer::Create();
	if (!GameRenderer::GetInstance()->Initialize(500,500)) {
		SDL_Log("Can not Initialize");
		return false;
	}

	LoadData();
	
	return true;
}

void Game::LoadData() {
	app = std::make_unique<Kura02>();
	timeObj = std::make_unique<Time>(60.0f);
	app->Start();

	//renderBoardがユーザーに指定されていないのであれば、デフォルトのものをセットする
	if (renderBoard==nullptr) {
		renderBoard = std::make_unique<GameObject>(PrimitiveType::BOARD, "./Assets/Shader/StandardRenderBoard.vert", "./Assets/Shader/StandardRenderBoard.frag", RenderType::FrameBuffer);
	}

	timelineObj = std::make_unique<TimelineObject>();
	app->Timeline(timelineObj.get());
	timelineObj->Initialize();
}

void Game::RunLoop() {
	while (isRunning)
	{
		if (isRestart) {
			Reflesh();
		}
		else {
			UpdateTimeline();
			InputProcess();
			UpdateGame();
			GenerateOutput();
		}
	}
}

void Game::UpdateTimeline() {
	static_cast<std::shared_ptr<class TimelineComponent>>(timelineObj->timelineComponent)->Update();

	std::sort(gameObjectList.begin(), gameObjectList.end(), [](GameObject* a, GameObject* b) {
		return a->renderOrder < b->renderOrder;
	});
}

void Game::InputProcess() {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseStateBool = true;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseStateBool = false;
			break;
		default:
			break;
		} 
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);

	for (auto obj : gameObjectList) {
		obj->ProcessInput(state);
	}

}

void Game::UpdateGame() {
	while (!(timeObj->GetTime() > previousTime + 16.0f)) { timeObj->UpdateTime(); };
	deltaTime = (timeObj->GetTime() - previousTime) / 1000.0f;
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	previousTime = static_cast<float>(timeObj->GetTime());
	time = previousTime;

	for (auto obj : gameObjectList) {
		obj->Update();
	}
	
	if (app) {
		app->Update();
	}
	
}
void Game::GenerateOutput() {
	GameRenderer::GetInstance()->Draw();
}

void Game::Reflesh() {
	//Listを解放
	gameObjectList.clear();
	boardGameObjectList.clear();
	postProcessGameObjectList.clear();
	uiObjectList.clear();

	//メンバ変数を初期化
	isRunning = true;
	time = 0.0f;
	deltaTime = 0.0f;
	previousTime = 0.0f;
	mouseStateBool = false;
	animTime = 0.0f;
	isRestart = false;

	//メモリを解放
	game_camera_instance = nullptr;
	timelineObj.reset();
	timeObj.reset();
	renderBoard.reset();
	if (app) {
		app.reset();
	}
	
	//再度リソースをロードする
	LoadData();
}

void Game::Restart() {
	isRestart = true;
}

void Game::ShutDown() {
	GameRenderer::GetInstance()->ShutDown();
	GameRenderer::Destroy();

	gameObjectList.clear();
	boardGameObjectList.clear();
	postProcessGameObjectList.clear();
	uiObjectList.clear();
}