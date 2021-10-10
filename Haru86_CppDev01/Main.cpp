#include "Main.h"
#include <iostream>
#include "./Game.h"

int main() {
	std::cout << "Hello World" << std::endl;
	Game game;
	if (game.Initialize()) {
		game.RunLoop();
	}
	game.ShutDown();
}