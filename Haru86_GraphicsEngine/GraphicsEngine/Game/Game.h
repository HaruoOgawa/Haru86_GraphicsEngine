#pragma once

#include "SDL.h"
#include "../Graphics/GameRenderer.h"
#include <vector>

#include <memory>
#include <map>
#include <GL/glew.h>

enum ERerderingTarget
{
	COLOR,
	DEPTH
};

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
	class RaymarchingObject* m_RaymarchingObject;
	
	friend class Main;
	friend class GameObject;
	friend class RaymarchingObject;
	friend class UIObject;
	friend class GameRenderer;
	friend class TimelineComponent;
	friend class UIComponent;
	friend class Material;
	friend class PostProcess;
	friend class CBloom;

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
	ERerderingTarget renderingTarget;
	
protected:
	static Game* s_pInstance;
};

