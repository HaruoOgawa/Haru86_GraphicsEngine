#include "Main.h"
#include <iostream>
#include "./Game.h"

int main(int argc, char** argv) {
	
	Game game;
	if (game.Initialize()) {
		std::cout << "Open Game" << std::endl;
		game.RunLoop();
	}
	game.ShutDown();

	return 0;
}