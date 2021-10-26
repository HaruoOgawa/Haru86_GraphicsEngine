#include "App.h"
#include "./GameObject.h"
#include "./TimelineObject.h"
#include "./UIComponent.h"
#include "./RectTransformComponent.h"


GameObject* Scene1_Frag;
GameObject* Scene2_Frag;

App::App()
{
	
}

App::~App() {

}
void App::Start() const {
	Scene1_Frag = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/VedaStructuredShader/scene1.frag");
	Scene2_Frag = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/VedaStructuredShader/scene2.frag");


	GameObject* uiButton = new GameObject(PrimitiveType::BOARD,"./Shader/UIStandard.vert","./Shader/UIStandard.frag");
	uiButton->SetScale(glm::vec3(0.1f,0.05f,1.0f)*0.5f);
	uiButton->AddComponent(new UIComponent(uiButton));
	uiButton->AddComponent(new RectTransformComponent(uiButton,0.1f,0.1f));

	GameObject* renderBoard = new GameObject(PrimitiveType::BOARD, "./Shader/VedaStructuredShader/BoardRender.vert", "./Shader/VedaStructuredShader/BoardRender.frag",RenderType::DefaultBuffer);
}
void App::Update() const {
	
}

void App::Timeline(TimelineObject* timeline) const {
	timeline->AddActivationClip(Scene1_Frag,0.0f,43.0f);
	timeline->AddActivationClip(Scene2_Frag, 43.0f, 65.0f);
}

