#include "GraphicsLearning.h"
#include "GraphicsEngine/Object/GameObject.h"
#include "GraphicsEngine/Component/TransformComponent.h"
#include "GraphicsEngine/Object/CameraObject.h"
#include "GraphicsEngine/Component/CameraComponent.h"
#include "GraphicsEngine/Object/CNode.h"
GraphicsLearning::GraphicsLearning() {

}

GraphicsLearning::~GraphicsLearning() {

}

void GraphicsLearning::Start() {
	cam_obj = std::make_shared<CameraObject>(CameraType::FIXED_CAMERA);
	cam_obj->m_cameraComponent->cameraCenter = glm::vec3(0.0, -1.0, 0.0);
	GraphicsMain::GetInstance()->game_camera_instance = cam_obj;
	cam_obj->GetRootNode()->GetComponent<TransformComponent>()->SetPosition(glm::vec3(8.5, 2.0, 8.5));

	GraphicsRenderer::GetInstance()->SetBackgroudColor(glm::vec4(glm::vec3(0.85f), 1.0));
	m_GraphObj = std::make_shared<GameObject>("Assets/Resources/glTFData/Dragon_1/Dragon_1.gltf");
	m_GraphObj->SetScale(glm::vec3(0.5f));
}

void GraphicsLearning::Update() {

}

void GraphicsLearning::Draw() {

}

void GraphicsLearning::Timeline(class TimelineObject* timelineObj) {

}