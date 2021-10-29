#include "Game.h"
#include <string>
#include "./GameObject.h"
#include "./VertexArray.h"
#include "./AudioObject.h"
#include "./AudioSourceComponent.h"
#include "./TimelineObject.h"
#include "./TimelineComponent.h"
#include "./Time.h"
#include <iostream>
#include <vector>
#include <algorithm>

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
	: gameRenderer(nullptr),
	isRunning(true),
	time(0.0f),
	deltaTime(0.0f),
	previousTime(0.0f),
	mouseStateBool(false),
	animTime(0.0f)
{
	app = new App();
	timeObj = new Time(60.0f);
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
	audioObj = new AudioObject();
	if (audioObj->Initialize()) {
		audioObj->PlayAudio();
	}

	app->Start();
	
	timelineObj = new TimelineObject();

	app->Timeline(timelineObj);
	timelineObj->Initialize();

}

void Game::RunLoop() {
	while (isRunning)
	{
		UpdateTimeline();
		InputProcess();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::UpdateTimeline() {
	static_cast<TimelineComponent*>(timelineObj->timelineComponent)->Update();

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
	app->Update();
	static_cast<AudioSourceComponent*>(audioObj->audioSource)->Update();
	
}
void Game::GenerateOutput() {
	GameRenderer::GetInstance()->Draw();
}



void Game::ShutDown() {
	GameRenderer::GetInstance()->ShutDown();
	//delete gameRenderer;
	GameRenderer::Destroy();
	delete app;
	delete audioObj;
	delete timelineObj;
	for (auto obj : gameObjectList) {
		delete obj;
	}

	for (auto obj : boardGameObjectList) {
		delete obj;
	}

	for (auto obj : postProcessGameObjectList) {
		delete obj;
	}

	for (auto obj : uiObjectList) {
		delete obj;
	}

	gameObjectList.clear();
	boardGameObjectList.clear();
	postProcessGameObjectList.clear();
	uiObjectList.clear();

}