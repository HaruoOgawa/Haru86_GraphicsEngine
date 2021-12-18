#include "Main.h"
#include <iostream>
#include "../../Game/Game.h"

int main(int argc, char** argv) {
	Game::Create();
	
	if (Game::GetInstance()->Initialize()) {
		Game::GetInstance()->RunLoop();
	}

	Game::GetInstance()->ShutDown();
	Game::Destroy();

	return 0;
}