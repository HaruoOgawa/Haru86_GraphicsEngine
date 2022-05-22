#include "AnimationLearning.h"
#include "GraphicsEngine/Object/TimelineObject.h"
#include "GraphicsEngine/Object/GameObject.h"

void AnimationLearning::Start() {
	// ”wŒiF
	GraphicsRenderer::GetInstance()->SetBackgroudColor(glm::vec4(glm::vec3(0.85f),1.0));
	
	//
	//m_AnimObj = std::make_shared<GameObject>("Assets/Resources/glTFData/Hakka/Hakka_v1.2.gltf");
	m_AnimObj = std::make_shared<GameObject>("Assets/Resources/glTFData/Woman/Woman.gltf");
	
	//
	m_GridPlane = std::make_shared<GameObject>(
		PrimitiveType::BOARD,
		"./Assets/Shader/GridPlane.frag"
	);
	m_GridPlane->SetRotation(glm::vec3(90.0f, 0.0, 0.0));
	m_GridPlane->SetPosition(glm::vec3(0.0f,0.0f,0.0f));
	m_GridPlane->SetScale(glm::vec3(25.0f));
}

void AnimationLearning::Update() {

}

void AnimationLearning::Draw() {

}

void AnimationLearning::Timeline(class TimelineObject* timelineObj) {

}