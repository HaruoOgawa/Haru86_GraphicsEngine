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
	class Time* timeObj;
	class TimelineObject* timelineObj;
	friend class GameObject;
	friend class UIObject;
	friend class GameRenderer;
	friend class TimelineComponent;
	friend class UIComponent;
private :
	void UpdateTimeline();
	void InputProcess();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	class GameRenderer* gameRenderer;
	bool isRunning;
	float previousTime;
	std::vector<class GameObject*> gameObjectList;
	std::vector<class GameObject*> boardGameObjectList;
	std::vector<class UIObject*> uiObjectList;
	class App* app;
	class AudioObject* audioObj;
	
	bool mouseStateBool;
protected:
	static Game* s_pInstance;
};

