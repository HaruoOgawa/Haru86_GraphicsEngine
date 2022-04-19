#include "CollisionArt.h"
#include "GraphicsEngine/Object/TimelineObject.h"
#include "GraphicsEngine/Component/TimelineComponent.h"
#include "GraphicsEngine/Object/GameObject.h"
#include "GraphicsEngine/Object/Object.h"
#include "GraphicsEngine/Component/TransformComponent.h"
#include "GraphicsEngine/Object/CameraObject.h"
#include "GraphicsEngine/Component/CameraComponent.h"
#include <glm/glm.hpp>
#include "GraphicsEngine/GraphicsMain/GraphicsMain.h"
#include "./Script/CCollisionGPUBox.h"
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
	GraphicsMain::GetInstance()->game_camera_instance = cam_obj.get();
	cam_obj->transform->SetPosition(glm::vec3(8.5,0.0, 8.5));

	//ins_cubes = std::make_unique<Object>();
	//ins_cubes->AddComponent<CCollisionGPUBox>(std::make_shared<CCollisionGPUBox>(ins_cubes.get()));
	
	test_SphereObj = std::make_unique<GameObject>(PrimitiveType::SPHERE);
	test_SphereObj->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
	test_SphereObj->AddCollider(physics::EColliderType::Sphere,physics::EObjectType::DYNAMIC);
	
	test_SphereObj2 = std::make_unique<GameObject>(PrimitiveType::SPHERE);
	test_SphereObj2->SetPosition(glm::vec3(5.2f, 10.0f, 5.2f));
	test_SphereObj2->AddCollider(physics::EColliderType::Sphere,physics::EObjectType::DYNAMIC);

	test_CubeObj = std::make_unique<GameObject>(PrimitiveType::CUBE);
	test_CubeObj->SetPosition(glm::vec3(0.0f,-5.0f,0.0));
	test_CubeObj->SetScale(glm::vec3(50.0f, 0.5f, 50.0f));
	test_CubeObj->AddCollider(physics::EColliderType::Box,physics::EObjectType::STATIC);

	// ポストプロセスの使用を宣言
	PostProcess::GetInstance()->EnablePostProcess();
	PostProcess::GetInstance()->EnableBloom(1.0,1.0);
}

void CollisionArt::Update() {
}

void CollisionArt::Draw() {
	//ins_cubes->GetComponent<CCollisionGPUBox>()->Draw();
}

void CollisionArt::Timeline(class TimelineObject* timelineObj) {

}