#include "App.h"
#include "./GameObject.h"
#include "./TimelineObject.h"
#include "./TimelineComponent.h"
#include "./UIComponent.h"
#include "./RectTransformComponent.h"
#include "./MeshRendererComponent.h"
#include "./Material.h"

GameObject* Scene1_Frag;
GameObject* Scene2_Frag;

//float animTime = 0.0f;

App::App()
{

}

App::~App() {

}
void App::Start()  {
	Scene1_Frag = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/VedaStructuredShader/scene1.frag");
	Scene2_Frag = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/VedaStructuredShader/scene2.frag");


	GameObject* uiButton = new GameObject(PrimitiveType::BOARD,"./Shader/UIStandard.vert","./Shader/UIStandard.frag");
	uiButton->SetScale(glm::vec3(0.1f,0.05f,1.0f)*0.5f);
	uiButton->AddComponent(new UIComponent(uiButton));
	uiButton->AddComponent(new RectTransformComponent(uiButton,0.1f,0.1f));

	GameObject* renderBoard = new GameObject(PrimitiveType::BOARD, "./Shader/VedaStructuredShader/BoardRender.vert", "./Shader/VedaStructuredShader/BoardRender.frag",RenderType::DefaultBuffer);

	GameObject* sampleFontTexture = new GameObject(PrimitiveType::BOARD, "./Shader/FontText.vert", "./Shader/FontText.frag","Demo Scene");

}
void App::Update()  {

}

void App::Timeline(TimelineObject* timeline)  {
	timeline->AddActivationClip(Scene1_Frag,0.0f,44.0f);
	timeline->AddActivationClip(Scene2_Frag, 44.0f, 65.0f);

	float startTime = 0.0f;
	float timeVal = 3.0f;
	float endTime = 0.0f;
	endTime += timeVal;

	Game* gamept = Game::GetInstance();

	for (int i = 0; i < (38 + 1) / 3;i++) {
		int val = i % 3;
		switch (val) {
		case 0:
			timeline->AddAnimationClip(Scene1_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [gamept]() {gamept->GetInstance()->animTime = 0.0f; Scene1_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 0); });
			break;
		case 1:
			timeline->AddAnimationClip(Scene1_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [gamept]() {gamept->GetInstance()->animTime = 0.0f; Scene1_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 1); });
			break;
		case 2:
			timeline->AddAnimationClip(Scene1_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [gamept]() {gamept->GetInstance()->animTime = 0.0f; Scene1_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 2); });
			break;
		default:
			break;

		}
		
	}

	timeline->AddAnimationClip(Scene1_Frag, 39.0,45.0, 
		[gamept]() {
			gamept->GetInstance()->animTime += gamept->GetInstance()->deltaTime;
			Scene1_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 3);
			Scene1_Frag->meshComp->material->SetFloatUniform("_cameraMoveVal", gamept->GetInstance()->animTime/6.0f);
			//printf(" gamept->GetInstance()->animTime/6.0f: %f \n", gamept->GetInstance()->animTime / 6.0f);
			//printf(" gamept->GetInstance()->time: %f \n", gamept->GetInstance()->time);

	});

	for (int i = 0; i < 21;i++) {
		int val = i % 3;
		switch (val) {
		case 0:
			timeline->AddAnimationClip(Scene2_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [] {Scene2_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 0); });
			break;
		case 1:
			timeline->AddAnimationClip(Scene2_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [] {Scene2_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 1); });
			break;
		case 2:
			timeline->AddAnimationClip(Scene2_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [] {Scene2_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 2); });
			break;
		default:
			break;

		}
	}

	
}

