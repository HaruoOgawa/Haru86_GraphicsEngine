#include "Main.h"
#include <iostream>
#include "./Game.h"
#include "./App/DemoSceneApp/App.h"

int main(int argc, char** argv) {
	Game::Create();
	Game::GetInstance()->app = new App();
	//Game game;
	if (Game::GetInstance()->Initialize()) {
		std::cout << "Open Game" << std::endl;
		Game::GetInstance()->RunLoop();
	}

	Game::GetInstance()->ShutDown();
	Game::Destroy();

	return 0;
}