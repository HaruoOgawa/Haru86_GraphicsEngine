#include "App.h"
#include "./GameObject.h"

App::App()
{

}

App::~App() {

}
void App::Start() const {
	GameObject* sampleQuad = new GameObject(PrimitiveType::BOARD);
	sampleQuad->SetPosition(glm::vec3(1.0f, 1.0f, 0.0f));
	sampleQuad->SetScale(glm::vec3(2.1f, 0.9f, 1.0f));
}
void App::Update() const {

}

