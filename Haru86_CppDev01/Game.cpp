#include "Game.h"
#include <string>
#include "./GameObject.h"
#include "./VertexArray.h"
#include "./AudioObject.h"
#include "./AudioSourceComponent.h"
#include "./TimelineObject.h"
#include "./TimelineComponent.h"
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
	previousTime(0.0f)
{
	app = new App();
}

Game::~Game() {
	
}

bool Game::Initialize() {
	if (SDL_Init(SDL_INIT_VIDEO||SDL_INIT_AUDIO)!=0) {
		SDL_Log("SDL Init is failure: %s", SDL_GetError());
		return false;
	}

	gameRenderer = new GameRenderer(this);
	if (!gameRenderer->Initialize(500,500)) {
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
		case SDLK_ESCAPE:
			isRunning = false;
			break;
		default:
			break;
		} 
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);

	
	for (auto obj : gameObjectList) {
		//printf("Call Input");
		obj->ProcessInput(state);
	}


}

void Game::UpdateGame() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), previousTime + 16.0f));
	deltaTime = (SDL_GetTicks() - previousTime) / 1000.0f;
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	previousTime = static_cast<float>(SDL_GetTicks());
	time = previousTime;

	app->Update();
	static_cast<AudioSourceComponent*>(audioObj->audioSource)->Update();
	
}
void Game::GenerateOutput() {
	gameRenderer->Draw();
}



void Game::ShutDown() {
	gameRenderer->ShutDown();
	delete gameRenderer;
	delete audioObj;
	delete timelineObj;
	for (auto obj : gameObjectList) {
		delete obj;
	}

	gameObjectList.clear();
	uiObjectList.clear();
}