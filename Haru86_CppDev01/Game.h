#pragma once

#include "SDL.h"
#include "./GameRenderer.h"

class Game
{
public:
	Game();
	~Game();
	bool Initialize();
	void RunLoop();
	void UpdateGame();
	void GenerateOutput();
	void ShutDown();
private :
	void InputProcess();
	class GameRenderer* gameRenderer;
	bool isRunning;
	
};

