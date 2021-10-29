#include "App.h"
#include "./GameObject.h"
#include "./TimelineObject.h"
#include "./TimelineComponent.h"
#include "./UIComponent.h"
#include "./RectTransformComponent.h"
#include "./MeshRendererComponent.h"
#include "./Material.h"

//ray
GameObject* Scene1_Frag;
GameObject* Scene2_Frag;

//font
GameObject* DemoText;
GameObject* MusicText;
GameObject* MyCreditText;
GameObject* TitleText;

//frame board
GameObject* renderBoard;

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

	renderBoard = new GameObject(PrimitiveType::BOARD, "./Shader/VedaStructuredShader/BoardRender.vert", "./Shader/VedaStructuredShader/BoardRender.frag",RenderType::FrameBuffer);

	DemoText = new GameObject(PrimitiveType::BOARD, "./Shader/FontText.vert", "./Shader/FontText.frag","Demo Scene");
	MusicText = new GameObject(PrimitiveType::BOARD, "./Shader/FontText.vert", "./Shader/FontText.frag","Music: lug00ber");
	MyCreditText = new GameObject(PrimitiveType::BOARD, "./Shader/FontText.vert", "./Shader/FontText.frag","Mouvie: Haru86_");
	TitleText = new GameObject(PrimitiveType::BOARD, "./Shader/FontText.vert", "./Shader/FontText.frag","Labyrinth");

}
void App::Update()  {
	//printf("Game::GetInstance()->deltaTime: %f \n",Game::GetInstance()->deltaTime);
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
			timeline->AddAnimationClip(Scene1_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [gamept](float val) {gamept->GetInstance()->animTime = 0.0f; Scene1_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 0); });
			break;
		case 1:
			timeline->AddAnimationClip(Scene1_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [gamept](float val) {gamept->GetInstance()->animTime = 0.0f; Scene1_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 1); });
			break;
		case 2:
			timeline->AddAnimationClip(Scene1_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [gamept](float val) {gamept->GetInstance()->animTime = 0.0f; Scene1_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 2); });
			break;
		default:
			break;

		}
		
	}

	timeline->AddAnimationClip(Scene1_Frag, 39.0,45.0, 
		[gamept](float val) {
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
			timeline->AddAnimationClip(Scene2_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [](float val) {Scene2_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 0); });
			break;
		case 1:
			timeline->AddAnimationClip(Scene2_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [] (float val){Scene2_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 1); });
			break;
		case 2:
			timeline->AddAnimationClip(Scene2_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [](float val) {Scene2_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 2); });
			break;
		default:
			break;

		}
	}


	timeline->AddActivationClip(DemoText, 2.0f, 12.0f);
	timeline->AddActivationClip(MusicText, 12.0f, 22.0f);
	timeline->AddActivationClip(MyCreditText, 22.0f, 32.0f);
	timeline->AddActivationClip(TitleText, 32.0f, 42.0f);
	
	timeline->AddAnimationClip(DemoText, 2.0f, 12.0f, [](float val) {
		
	//printf("val: %f \n", val);
	
	float delayVal = 0.2f;
	if (val<= delayVal) {
		DemoText->meshComp->material->SetFloatUniform("_alpha", val/ delayVal);
	}
	else if (val > delayVal && val < 1.0f- delayVal) {
		DemoText->meshComp->material->SetFloatUniform("_alpha", 1.0f);
	}
	else if (val>=1.0f- delayVal) {
		DemoText->meshComp->material->SetFloatUniform("_alpha", (1.0f - val)/delayVal);
	}

	});

	timeline->AddAnimationClip(MusicText, 12.0f, 22.0f, [](float val) {
		
		//printf("val: %f \n", val);

		float delayVal = 0.2f;
		if (val <= delayVal) {
			MusicText->meshComp->material->SetFloatUniform("_alpha", val / delayVal);
		}
		else if (val > delayVal && val < 1.0f - delayVal) {
			MusicText->meshComp->material->SetFloatUniform("_alpha", 1.0f);
		}
		else if (val >= 1.0f - delayVal) {
			MusicText->meshComp->material->SetFloatUniform("_alpha", (1.0f - val) / delayVal);
		}

	});
	timeline->AddAnimationClip(MyCreditText, 22.0f, 32.0f, [](float val) {
		
		//printf("val: %f \n", val);

		float delayVal = 0.2f;
		if (val <= delayVal) {
			MyCreditText->meshComp->material->SetFloatUniform("_alpha", val / delayVal);
		}
		else if (val > delayVal && val < 1.0f - delayVal) {
			MyCreditText->meshComp->material->SetFloatUniform("_alpha", 1.0f);
		}
		else if (val >= 1.0f - delayVal) {
			MyCreditText->meshComp->material->SetFloatUniform("_alpha", (1.0f - val) / delayVal);
		}

	});
	timeline->AddAnimationClip(TitleText, 32.0f, 42.0f, [](float val) {
		
		//printf("val: %f \n", val);

		float delayVal = 0.2f;
		if (val <= delayVal) {
			TitleText->meshComp->material->SetFloatUniform("_alpha", val / delayVal);
		}
		else if (val > delayVal && val < 1.0f - delayVal) {
			TitleText->meshComp->material->SetFloatUniform("_alpha", 1.0f);
		}
		else if (val >= 1.0f - delayVal) {
			TitleText->meshComp->material->SetFloatUniform("_alpha", (1.0f - val) / delayVal);
		}

	});

	//frame board
	timeline->AddAnimationClip(renderBoard, 0.0f, 2.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",0); });
	timeline->AddAnimationClip(renderBoard, 2.0f, 6.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",1); });
	timeline->AddAnimationClip(renderBoard, 6.0f, 8.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",0); });
	
}

