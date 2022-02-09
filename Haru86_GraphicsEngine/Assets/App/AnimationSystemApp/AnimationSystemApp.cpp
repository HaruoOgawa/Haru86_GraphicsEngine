#include "AnimationSystemApp.h"
#include "GraphicsEngine/Object/GameObject.h"
#include "GraphicsEngine/Graphics/GraphicsRenderer.h"
#include <glm/glm.hpp>
#include "GraphicsEngine/Component/MeshRendererComponent.h"

AnimationSystemApp::AnimationSystemApp()
	:BaseApp()
{

}

AnimationSystemApp::~AnimationSystemApp() {

}
void AnimationSystemApp::Start() {
	GraphicsRenderer::GetInstance()->SetBackgroundColor(glm::vec3(1.0,1.0,1.0));

	m_Plane = std::make_unique<GameObject>(PrimitiveType::BOARD,"./Assets/Shader/Standard.vert","./Assets/Shader/AnimationSystemApp/VRMSpace.frag");
	m_Plane->SetRotation(glm::quat(glm::vec3(90.0,0.0,0.0)));
	m_Plane->SetPosition(glm::vec3(0.0, 4.0, 0.0));
	m_Plane->SetScale(glm::vec3(100.0, 100.0, 100.0));
	m_Plane->meshComp->useAlphaTest = true;

	m_Ceiling = std::make_unique<GameObject>(PrimitiveType::BOARD, "./Assets/Shader/Standard.vert", "./Assets/Shader/AnimationSystemApp/VRMSpace.frag");
	m_Ceiling->SetRotation(glm::quat(glm::vec3(90.0, 0.0, 0.0)));
	m_Ceiling->SetPosition(glm::vec3(0.0, -4.0, 0.0));
	m_Ceiling->SetScale(glm::vec3(100.0, 100.0, 100.0));
}
void AnimationSystemApp::Update() {

}

void AnimationSystemApp::Draw() {

}

void AnimationSystemApp::Timeline(TimelineObject* timelineObj) {

}