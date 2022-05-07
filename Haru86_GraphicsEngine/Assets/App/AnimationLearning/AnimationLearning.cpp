#include "AnimationLearning.h"
#include "GraphicsEngine/Object/TimelineObject.h"
#include "GraphicsEngine/Object/GameObject.h"

void AnimationLearning::Start() {
	m_AnimObj = std::make_shared<GameObject>(PrimitiveType::SPHERE);
}

void AnimationLearning::Update() {

}

void AnimationLearning::Draw() {

}

void AnimationLearning::Timeline(class TimelineObject* timelineObj) {

}