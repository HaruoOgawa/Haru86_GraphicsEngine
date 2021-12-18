#pragma once

#include "SDL.h"
#include "../Graphics/GameRenderer.h"
#include <vector>
#include "../App/BaseApp/BaseApp.h"
#include <memory>
#include <map>
#include <GL/glew.h>

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
	void Restart();
	float time;
	float deltaTime;
	std::unique_ptr<class Time> timeObj;
	std::unique_ptr<class TimelineObject> timelineObj;
	float animTime;

	std::unique_ptr<class BaseApp> app;
	//frame board
	std::unique_ptr<class GameObject> renderBoard;
	class CameraObject* game_camera_instance;
	std::map<int, GLenum> texSlots;

	friend class Main;
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
	void Reflesh();
	bool isRunning;
	float previousTime;
	std::vector<class GameObject*> gameObjectList;
	std::vector<class GameObject*> boardGameObjectList;
	std::vector<class GameObject*> postProcessGameObjectList;
	std::vector<class UIObject*> uiObjectList;
	
	bool mouseStateBool;
	bool isRestart;
	
protected:
	static Game* s_pInstance;
};

