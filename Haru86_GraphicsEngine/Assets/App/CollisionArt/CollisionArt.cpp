#include "CollisionArt.h"
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

CollisionArt::CollisionArt():
	BaseApp()
{

}

CollisionArt::~CollisionArt() {
	printf("CollisionArt is Released\n");
}

void CollisionArt::Start() {
	cam_obj = std::make_unique<CameraObject>(CameraType::FIXED_CAMERA);
	//cam_obj->SetPosition(glm::vec3(0.0, 0.0, -3.0));
	cam_obj->m_cameraComponent->cameraCenter = glm::vec3(0.0,-1.0,0.0);
	Game::GetInstance()->game_camera_instance = cam_obj.get();
	cam_obj->transform->position = glm::vec3(8.5,0.0, 8.5);

	ins_cubes = std::make_unique<Object>();
	ins_cubes->AddComponent<CBoxInstancing>(std::make_shared<CBoxInstancing>(ins_cubes.get()));
	
	// ポストプロセスの使用を宣言
	PostProcess::GetInstance()->EnablePostProcess();
	PostProcess::GetInstance()->EnableBloom(1.0,1.0);
}

void CollisionArt::Update() {
}

void CollisionArt::Draw() {
	ins_cubes->GetComponent<CBoxInstancing>()->Draw();
}

void CollisionArt::Timeline(class TimelineObject* timelineObj) {

}