#include "CC220108App.h"
#include "GraphicsEngine/Object/TimelineObject.h"
#include "GraphicsEngine/Component/TimelineComponent.h"
#include "GraphicsEngine/Object/GameObject.h"
#include "GraphicsEngine/Component/TransformComponent.h"
#include "GraphicsEngine/Object/CameraObject.h"
#include <glm/glm.hpp>
#include "GraphicsEngine/Game/Game.h"

CC220108App::CC220108App():
	BaseApp()
{

}

CC220108App::~CC220108App() {

}

void CC220108App::Start() {
	cam_obj = std::make_unique<CameraObject>(CameraType::FIXED_CAMERA);
	cam_obj->SetPosition(glm::vec3(0.0, 0.0, -3.0));
	Game::GetInstance()->game_camera_instance = cam_obj.get();

	ins_cubes = std::make_unique<GameObject>(PrimitiveType::CUBE);
	//ins_cubes->SetScale(glm::vec3(100.0, 100.0, 100.0));

}

void CC220108App::Update() {

}

void CC220108App::Draw() {

}

void CC220108App::Timeline(class TimelineObject* timelineObj) {

}