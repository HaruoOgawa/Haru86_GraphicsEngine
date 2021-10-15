#include "App.h"
#include "./GameObject.h"

App::App(Game* g)
	: game(g)
{

}

App::~App() {

}
void App::Start() {
	GameObject* sampleQuad = new GameObject(game, PrimitiveType::BOARD);
	sampleQuad->SetPosition(glm::vec3(1.0f, 1.0f, 0.0f));
	sampleQuad->SetScale(glm::vec3(2.1f, 0.9f, 1.0f));
}
void App::Update() {

}