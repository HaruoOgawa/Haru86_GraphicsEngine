#include "Game.h"

Game::Game()
	: gameRenderer(nullptr),
	isRunning(true)
{

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
		//delete gameRenderer;
		return false;
	}
	
	return true;
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

}
void Game::GenerateOutput() {
	gameRenderer->Draw();
}

void Game::ShutDown() {
	gameRenderer->ShutDown();
	delete gameRenderer;
}