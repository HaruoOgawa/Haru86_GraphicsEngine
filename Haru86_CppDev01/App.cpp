#include "App.h"
#include "./GameObject.h"
#include "./TimelineObject.h"
#include "./UIComponent.h"

GameObject* sampleRay;

App::App()
{
	
}

App::~App() {

}
void App::Start() const {
	sampleRay = new GameObject(PrimitiveType::BOARD, "./demo.vert", "./Haru86_Hexagon.frag");

	//GameObject* uiButton = new GameObject(PrimitiveType::BOARD, "./UIStandard.vert", "./UIStandard.frag");
	//uiButton->AddComponent(new UIComponent(uiButton));
}
void App::Update() const {

}

void App::Timeline(TimelineObject* timeline) const {
	
}

