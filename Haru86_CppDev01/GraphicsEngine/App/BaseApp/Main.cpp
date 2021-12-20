#include "Main.h"
#include <iostream>
#include "../../Game/Game.h"

int main(int argc, char** argv) {
	Game::Create();
	
	if (Game::GetInstance()->Initialize()) {
		Game::GetInstance()->RunLoop();
	}

	//printf("Game is Finished\n");

	Game::GetInstance()->ShutDown();
	Game::Destroy();

	//printf("Game is Destroyed\n");

	return 0;
}