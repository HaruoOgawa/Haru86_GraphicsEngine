#pragma once

#include "SDL.h"
#include "./GameRenderer.h"
#include <vector>
//#include "./GameObject.h"

class Game
{
public:
	Game();
	~Game();
	bool Initialize();
	void RunLoop();
	void ShutDown();
	std::vector<class GameObject*> gameObjectList;
	float time;
	float deltaTime;
private :
	void InputProcess();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	class GameRenderer* gameRenderer;
	bool isRunning;
	float previousTime;
};

