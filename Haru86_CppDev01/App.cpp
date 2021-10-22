#include "App.h"
#include "./GameObject.h"
#include "./TimelineObject.h"
#include "./UIComponent.h"

GameObject* sampleQuad;
GameObject* sampleQuad2;
GameObject* sampleCube;
GameObject* sampleSphere;
GameObject* cube;

App::App()
{

}

App::~App() {

}
void App::Start() const {
	sampleQuad = new GameObject(PrimitiveType::BOARD);
	sampleQuad->SetPosition(glm::vec3(1.0f, 1.0f, 0.0f));
	sampleQuad->SetScale(glm::vec3(1.1f, 0.9f, 1.0f));

	sampleQuad2 = new GameObject(PrimitiveType::BOARD);
	sampleQuad2->SetPosition(glm::vec3(-1.0f, 1.0f, 0.0f));
	sampleQuad2->SetScale(glm::vec3(1.1f, 0.9f, 1.0f));

	sampleCube = new GameObject(PrimitiveType::CUBE);
	sampleCube->SetPosition(glm::vec3(-2., -1, 1));
	sampleCube->SetScale(glm::vec3(1.2f, 1.5f, 0.75f));

	sampleSphere = new GameObject(PrimitiveType::SPHERE);
	sampleSphere->SetPosition(glm::vec3(1.5f, -1.0f, 0));
	sampleSphere->SetScale(glm::vec3(0.5f, 0.5f, 0.5f));

	cube = new GameObject(PrimitiveType::CUBE);
	cube->SetPosition(glm::vec3(0.1f, 0.2f, 0.0f));
	cube->SetScale(glm::vec3(1.0f, 1.0f, 1.0f));

	GameObject* uiButton = new GameObject(PrimitiveType::BOARD, "./UIStandard.vert", "./UIStandard.frag");
	uiButton->AddComponent(new UIComponent(uiButton));
}
void App::Update() const {

}

void App::Timeline(TimelineObject* timeline) const {
	timeline->AddActivationClip(sampleSphere, 10.0f, 15.0f);
	timeline->AddActivationClip(sampleSphere, 8.0f, 13.0f);

	/*timeline->AddActivationClip(sampleQuad, 1.0f, 7.5f);
	timeline->AddActivationClip(sampleQuad2, 8.0f, 13.0f);
	timeline->AddActivationClip(sampleCube, 15.0f, 20.0f);
	timeline->AddActivationClip(cube, 3.0f, 18.0f);
	timeline->AddActivationClip(sampleSphere, 20.0f, 25.0f);*/

	timeline->AddCustomClip(cube, 10.0f, 15.0f, []() {printf("Hello randa in comp \n"); });
	timeline->AddCustomClip(sampleCube, 5.0f, 13.0f, []() {printf("Hello randa 2222 in comp \n"); });
}

