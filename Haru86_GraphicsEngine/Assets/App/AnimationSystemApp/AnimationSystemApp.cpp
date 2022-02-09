#include "AnimationSystemApp.h"
#include "GraphicsEngine/Object/GameObject.h"
#include "GraphicsEngine/Graphics/GraphicsRenderer.h"
#include <glm/glm.hpp>

AnimationSystemApp::AnimationSystemApp()
	:BaseApp()
{

}

AnimationSystemApp::~AnimationSystemApp() {

}
void AnimationSystemApp::Start() {
	GraphicsRenderer::GetInstance()->SetBackgroundColor(glm::vec3(1.0,1.0,1.0));
}
void AnimationSystemApp::Update() {

}

void AnimationSystemApp::Draw() {

}

void AnimationSystemApp::Timeline(TimelineObject* timelineObj) {

}