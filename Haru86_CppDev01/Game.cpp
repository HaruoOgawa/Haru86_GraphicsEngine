#include "Game.h"
#include <string>
#include "./GameObject.h"
#include "./VertexArray.h"

Game::Game()
	: gameRenderer(nullptr),
	isRunning(true),
	time(0.0f),
	deltaTime(0.0f),
	previousTime(0.0f)
{
	app = new App(this);
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
	/*GameObject* sampleQuad = new GameObject(this,PrimitiveType::BOARD);
	sampleQuad->SetPosition(glm::vec3(1.0f, 1.0f, 0.0f));
	sampleQuad->SetScale(glm::vec3(2.1f, 0.9f, 1.0f));*/
	app->Start();
}

void Game::RunLoop() {
	while (isRunning)
	{
		InputProcess();
		UpdateGame();
		GenerateOutput();
	}
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
		default:
			break;
		} 
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
}
void Game::GenerateOutput() {
	gameRenderer->Draw();
}



void Game::ShutDown() {
	gameRenderer->ShutDown();
	delete gameRenderer;
	for (auto obj : gameObjectList) {
		delete obj;
	}
}