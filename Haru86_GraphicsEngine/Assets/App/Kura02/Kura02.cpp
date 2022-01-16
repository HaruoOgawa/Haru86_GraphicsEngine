#include "Kura02.h"
#include "GraphicsEngine/Object/TimelineObject.h"
#include "GraphicsEngine/Component/TimelineComponent.h"
#include "GraphicsEngine/Object/GameObject.h"
#include "GraphicsEngine/Object/Object.h"
#include "GraphicsEngine/Component/TransformComponent.h"
#include "GraphicsEngine/Object/CameraObject.h"
#include "GraphicsEngine/Component/CameraComponent.h"
#include <glm/glm.hpp>
#include "GraphicsEngine/Game/Game.h"
#include "./Script/CBoxInstancing.h"

Kura02::Kura02():
	BaseApp()
{

}

Kura02::~Kura02() {

}

void Kura02::Start() {
	cam_obj = std::make_unique<CameraObject>(CameraType::FIXED_CAMERA);
	//cam_obj->SetPosition(glm::vec3(0.0, 0.0, -3.0));
	cam_obj->m_cameraComponent->cameraCenter = glm::vec3(0.0,-0.5,0.0);
	Game::GetInstance()->game_camera_instance = cam_obj.get();

	ins_cubes = std::make_unique<Object>();
	ins_cubes->AddComponent(std::make_shared<CBoxInstancing>(ins_cubes.get()));
	
}

void Kura02::Update() {
	ins_cubes->Update();
	cam_obj->transform->position = glm::vec3(
		glm::cos(Game::GetInstance()->time * 0.0001),
		0.0, 
		glm::sin(Game::GetInstance()->time * 0.0001)
	);
}

void Kura02::Draw() {
	static_cast<CBoxInstancing*>(ins_cubes->GetComponent(static_cast<std::string>(typeid(CBoxInstancing).name())))->Draw();
}

void Kura02::Timeline(class TimelineObject* timelineObj) {

}