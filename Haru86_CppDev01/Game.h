#pragma once

#include "SDL.h"
#include "./GameRenderer.h"
#include <vector>
#include "./App.h"

class Game
{
public:
	static Game* GetInstance()
	{
		return s_pInstance;
	}

	static void Create();
	static void Destroy();

	Game();
	~Game();
	bool Initialize();
	void RunLoop();
	void ShutDown();
	float time;
	float deltaTime;
	friend class GameObject;
	friend class GameRenderer;
private :
	void InputProcess();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	class GameRenderer* gameRenderer;
	bool isRunning;
	float previousTime;
	std::vector<class GameObject*> gameObjectList;
	class App* app;
	class AudioObject* audioObj;
	class TimelineObject* timelineObj;
protected:
	static Game* s_pInstance;
};

