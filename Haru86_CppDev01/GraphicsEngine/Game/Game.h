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
	class Time* timeObj;
	class TimelineObject* timelineObj;
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
	class GameRenderer* gameRenderer;
	bool isRunning;
	float previousTime;
	std::vector<class GameObject*> gameObjectList;
	std::vector<class GameObject*> boardGameObjectList;
	std::vector<class GameObject*> postProcessGameObjectList;
	std::vector<class UIObject*> uiObjectList;
	
	bool mouseStateBool;
	
protected:
	static Game* s_pInstance;
};

