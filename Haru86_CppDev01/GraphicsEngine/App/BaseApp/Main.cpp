#include "Main.h"
#include <iostream>
#include "../../Game/Game.h"
#include "../../../Assets/App/KuraArtApp/KuraArtApp.h"

int main(int argc, char** argv) {
	Game::Create();
	Game::GetInstance()->app = std::make_unique<KuraArtApp>();
	
	if (Game::GetInstance()->Initialize()) {
		Game::GetInstance()->RunLoop();
	}

	Game::GetInstance()->ShutDown();
	Game::Destroy();

	return 0;
}