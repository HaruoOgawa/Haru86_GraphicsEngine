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
	float time;
	float deltaTime;
	std::shared_ptr<class Time> timeObj;
	std::shared_ptr<class TimelineObject> timelineObj;
	float animTime;

	class BaseApp* app;
	//frame board
	std::shared_ptr<class GameObject> renderBoard;
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
	std::shared_ptr<class GameRenderer> gameRenderer;
	bool isRunning;
	float previousTime;
	std::vector<std::shared_ptr<class GameObject>> gameObjectList;
	std::vector<std::shared_ptr<class GameObject>> boardGameObjectList;
	std::vector<std::shared_ptr<class GameObject>> postProcessGameObjectList;
	std::vector<std::shared_ptr<class UIObject>> uiObjectList;
	
	bool mouseStateBool;
	
protected:
	static Game* s_pInstance;
};

