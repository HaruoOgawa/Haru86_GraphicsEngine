#include "GraphicsMain.h"
#include <string>
#include "../Object/GameObject.h"
#include "../Graphics/Mesh.h"
#include "../Component/AudioSourceComponent.h"
#include "../Object/TimelineObject.h"
#include "../Component/TimelineComponent.h"
#include "./Time.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "../App/BaseApp/BaseApp.h"
#include "../../Assets/App/CollisionArt/CollisionArt.h"
//#include "../../Assets/App/KuraArtApp/KuraArtApp.h"
//#include "../../Assets/App/DemoApp/DemoApp.h"
#include <exception>
#include <stdexcept>
#include "GraphicsEngine/Object/RaymarchingObject.h"
#include "GraphicsEngine/Object/CameraObject.h"

GraphicsMain* GraphicsMain::s_pInstance = nullptr;

void GraphicsMain::Create()
{
	if (!s_pInstance)
	{
		s_pInstance = new GraphicsMain;
	}
}

void GraphicsMain::Destroy()
{
	delete s_pInstance;
	s_pInstance = nullptr;
}

GraphicsMain::GraphicsMain()
	: 
	isRunning(true),
	time(0.0f),
	deltaTime(0.0f),
	previousTime(0.0f),
	mouseStateBool(false),
	animTime(0.0f),
	isRestart(false),
	renderingTarget(ERerderingTarget::COLOR),
	m_RaymarchingObject(nullptr)
{
	
	for (int i = 0; i < 20;i++) {
		switch (i)
		{
		case 0:
			texSlots.emplace(i, GL_TEXTURE0);
			break;
		case 1:
			texSlots.emplace(i, GL_TEXTURE1);
			break;
		case 2:
			texSlots.emplace(i, GL_TEXTURE2);
			break;
		case 3:
			texSlots.emplace(i, GL_TEXTURE3);
			break;
		case 4:
			texSlots.emplace(i, GL_TEXTURE4);
			break;
		case 5:
			texSlots.emplace(i, GL_TEXTURE5);
			break;
		case 6:
			texSlots.emplace(i, GL_TEXTURE6);
			break;
		case 7:
			texSlots.emplace(i, GL_TEXTURE7);
			break;
		case 8:
			texSlots.emplace(i, GL_TEXTURE8);
			break;
		case 9:
			texSlots.emplace(i, GL_TEXTURE9);
			break;
		case 10:
			texSlots.emplace(i, GL_TEXTURE10);
			break;
		case 11:
			texSlots.emplace(i, GL_TEXTURE11);
			break;
		case 12:
			texSlots.emplace(i, GL_TEXTURE12);
			break;
		case 13:
			texSlots.emplace(i, GL_TEXTURE13);
			break;
		case 14:
			texSlots.emplace(i, GL_TEXTURE14);
			break;
		case 15:
			texSlots.emplace(i, GL_TEXTURE15);
			break;
		case 16:
			texSlots.emplace(i, GL_TEXTURE16);
			break;
		case 17:
			texSlots.emplace(i, GL_TEXTURE17);
			break;
		case 18:
			texSlots.emplace(i, GL_TEXTURE18);
			break;
		case 19:
			texSlots.emplace(i, GL_TEXTURE19);
			break;
		default:
			break;
		}
	}
}

GraphicsMain::~GraphicsMain() {
	
}

bool GraphicsMain::Initialize() {
	if (SDL_Init(SDL_INIT_VIDEO||SDL_INIT_AUDIO)!=0) {
		SDL_Log("SDL Init is failure: %s", SDL_GetError());
		return false;
	}

	GraphicsRenderer::Create();
	if (!GraphicsRenderer::GetInstance()->Initialize(500,500)) {
		SDL_Log("Can not Initialize");
		return false;
	}

	LoadData();
	
	return true;
}

void GraphicsMain::LoadData() {
	app = std::make_unique<CollisionArt>();
	timeObj = std::make_unique<Time>(60.0f);
	app->Start();

	//renderBoardがユーザーに指定されていないのであれば、デフォルトのものをセットする
	if (renderBoard==nullptr) {
		renderBoard = std::make_unique<GameObject>(PrimitiveType::BOARD, "./Assets/Shader/StandardRenderBoard.vert", "./Assets/Shader/StandardRenderBoard.frag", RenderType::FrameBuffer);
	}

	timelineObj = std::make_unique<TimelineObject>();
	app->Timeline(timelineObj.get());
	timelineObj->Initialize();
}

void GraphicsMain::RunLoop() {
	while (isRunning)
	{
		if (isRestart) {
			Reflesh();
		}
		else {
			UpdateTimeline();
			InputProcess();
			Update();
			// UpdatePhysics	
			Draw();
		}
	}
}

void GraphicsMain::UpdateTimeline() {
	static_cast<std::shared_ptr<class TimelineComponent>>(timelineObj->timelineComponent)->Update();

	std::sort(gameObjectList.begin(), gameObjectList.end(), [](GameObject* a, GameObject* b) {
		return a->renderOrder < b->renderOrder;
	});
}

void GraphicsMain::InputProcess() {
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseStateBool = true;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseStateBool = false;
			break;
		default:
			break;
		} 
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);

	for (auto obj : gameObjectList) {
		obj->ProcessInput(e);
	}

	game_camera_instance->ProcessInput(e);

}

void GraphicsMain::Update() {
	while (!(timeObj->GetTime() > previousTime + 16.0f)) { timeObj->UpdateTime(); };
	deltaTime = (timeObj->GetTime() - previousTime) / 1000.0f;
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	previousTime = static_cast<float>(timeObj->GetTime());
	time = previousTime;

	for (auto obj : gameObjectList) {
		obj->Update();
	}
	
	if (app) {
		app->Update();
	}

	game_camera_instance->Update();
	
}
void GraphicsMain::Draw() {
	GraphicsRenderer::GetInstance()->Draw();
}

void GraphicsMain::Reflesh() {
	//Listを解放
	gameObjectList.clear();
	boardGameObjectList.clear();
	postProcessGameObjectList.clear();
	uiObjectList.clear();

	//メンバ変数を初期化
	isRunning = true;
	time = 0.0f;
	deltaTime = 0.0f;
	previousTime = 0.0f;
	mouseStateBool = false;
	animTime = 0.0f;
	isRestart = false;
	renderingTarget = ERerderingTarget::COLOR;

	//メモリを解放
	game_camera_instance = nullptr;
	timelineObj.reset();
	timeObj.reset();
	renderBoard.reset();
	if (app) {
		app.reset();
	}
	m_RaymarchingObject = nullptr;
	
	//再度リソースをロードする
	LoadData();
}

void GraphicsMain::Restart() {
	isRestart = true;
}

void GraphicsMain::ShutDown() {
	GraphicsRenderer::GetInstance()->ShutDown();
	GraphicsRenderer::Destroy();

	gameObjectList.clear();
	boardGameObjectList.clear();
	postProcessGameObjectList.clear();
	uiObjectList.clear();
}