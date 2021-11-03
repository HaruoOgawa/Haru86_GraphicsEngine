#include "Main.h"
#include <iostream>
#include "./Game.h"

int main(int argc, char** argv) {
	Game::Create();
	//Game game;
	if (Game::GetInstance()->Initialize()) {
		std::cout << "Open Game" << std::endl;
		Game::GetInstance()->RunLoop();
	}

	Game::GetInstance()->ShutDown();
	Game::Destroy();

	return 0;
}