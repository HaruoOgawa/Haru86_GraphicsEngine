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
	sampleQuad->SetScale(glm::vec3(1.1f, 0.9f, 1.0f));

	GameObject* sampleQuad2 = new GameObject(PrimitiveType::BOARD);
	sampleQuad2->SetPosition(glm::vec3(-1.0f, 1.0f, 0.0f));
	sampleQuad2->SetScale(glm::vec3(1.1f, 0.9f, 1.0f));

	GameObject* sampleCube = new GameObject(PrimitiveType::CUBE);
	sampleCube->SetPosition(glm::vec3(-2., -1, 1));
	sampleCube->SetScale(glm::vec3(1.2f, 1.5f, 0.75f));

	GameObject* sampleSphere = new GameObject(PrimitiveType::SPHERE);
	sampleSphere->SetPosition(glm::vec3(1.5f, -1.0f, 0));
	sampleSphere->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));

	GameObject* cube = new GameObject(PrimitiveType::CUBE);
	cube->SetPosition(glm::vec3(0.1f, 0.2f, 0.0f));
	cube->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	
}
void App::Update() const {

}

