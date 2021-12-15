#include "Main.h"
#include <iostream>
#include "../../Game/Game.h"
#include "../../../Assets/App/DemoApp/DemoApp.h"

int main(int argc, char** argv) {
	Game::Create();
	Game::GetInstance()->app = new DemoApp();
	
	if (Game::GetInstance()->Initialize()) {
		//std::cout << "Open Game" << std::endl;
		Game::GetInstance()->RunLoop();
	}

	Game::GetInstance()->ShutDown();
	Game::Destroy();

	return 0;
}