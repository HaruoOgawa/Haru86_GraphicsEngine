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
#include "GraphicsEngine/Object/RaymarchingObject.h"
#include "GraphicsEngine/Graphics/PostProcess.h"
#include "Script/CKura3DGPUTrail.h"

Kura02::Kura02():
	BaseApp()
{

}

Kura02::~Kura02() {

}

void Kura02::Start() {
	cam_obj = std::make_unique<CameraObject>(CameraType::FIXED_CAMERA);
	//cam_obj->SetPosition(glm::vec3(0.0, 0.0, -3.0));
	cam_obj->m_cameraComponent->cameraCenter = glm::vec3(0.0,-1.0,0.0);
	Game::GetInstance()->game_camera_instance = cam_obj.get();
	cam_obj->transform->position = glm::vec3(5.0,0.0,5.0);

	ins_cubes = std::make_unique<Object>();
	ins_cubes->AddComponent(std::make_shared<CBoxInstancing>(ins_cubes.get()));
	ins_cubes->AddComponent(std::make_shared<CKura3DGPUTrail>(ins_cubes.get()));

	raymarching_obj = std::make_unique<RaymarchingObject>("./Assets/Shader/Kura02/CubeFieldRaymarching.frag");
	Game::GetInstance()->m_RaymarchingObject = raymarching_obj.get();

	// ポストプロセスの使用を宣言
	PostProcess::GetInstance()->EnablePostProcess();
	PostProcess::GetInstance()->EnableBloom(1.0,1.0);
}

void Kura02::Update() {
	ins_cubes->Update();
	cam_obj->transform->position = glm::vec3(
		glm::cos(Game::GetInstance()->time * 0.0001)*10.0,
		0.0, 
		glm::sin(Game::GetInstance()->time * 0.0001)*10.0
	);

}

void Kura02::Draw() {
	static_cast<CBoxInstancing*>(ins_cubes->GetComponent(static_cast<std::string>(typeid(CBoxInstancing).name())))->Draw();
	static_cast<CKura3DGPUTrail*>(ins_cubes->GetComponent(static_cast<std::string>(typeid(CKura3DGPUTrail).name())))->Draw();
}

void Kura02::Timeline(class TimelineObject* timelineObj) {

}