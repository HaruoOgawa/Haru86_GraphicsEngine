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


	/*GameObject* uiButton = new GameObject(PrimitiveType::BOARD,"./Shader/UIStandard.vert","./Shader/UIStandard.frag");
	uiButton->SetScale(glm::vec3(0.1f,0.05f,1.0f)*0.5f);
	uiButton->AddComponent(new UIComponent(uiButton));
	uiButton->AddComponent(new RectTransformComponent(uiButton,0.1f,0.1f));*/

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
	timeline->AddActivationClip(Scene1_Frag,0.0f,42.0f);
	timeline->AddActivationClip(Scene2_Frag, 42.0f, 64.0f);

	float startTime = 0.0f;
	float timeVal = 3.0f;
	float endTime = 0.0f;
	endTime += timeVal;

	Game* gamept = Game::GetInstance();

	for (int i = 0; i < 13;i++) {
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

	timeline->AddAnimationClip(Scene1_Frag, 38.0f, 42.0f,
		[gamept](float val) {
			gamept->GetInstance()->animTime += gamept->GetInstance()->deltaTime;
			Scene1_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 3);
			Scene1_Frag->meshComp->material->SetFloatUniform("_cameraMoveVal", val);
			

	});

	startTime = 42.0f;
	endTime = startTime + 3.0;

	for (int i = 0; i < 6;i++) {
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
	timeline->AddAnimationClip(Scene2_Frag, static_cast<float>(57), static_cast<float>(64.0), [](float val) {Scene2_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 0);  });


	timeline->AddActivationClip(DemoText, 0.0f, 10.0f);
	timeline->AddActivationClip(MusicText, 10.0f, 20.0f);
	timeline->AddActivationClip(MyCreditText, 20.0f, 30.0f);
	timeline->AddActivationClip(TitleText, 30.0f, 40.0f);
	
	timeline->AddAnimationClip(DemoText, 0.0f, 10.0f, [](float val) {
		
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

	timeline->AddAnimationClip(MusicText, 10.0f, 20.0f, [](float val) {
		
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
	timeline->AddAnimationClip(MyCreditText, 20.0f, 30.0f, [](float val) {
		
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
	timeline->AddAnimationClip(TitleText, 30.0f, 40.0f, [](float val) {
		
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
	timeline->AddAnimationClip(renderBoard, 0.0f, 38.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",0); });
	timeline->AddAnimationClip(renderBoard, 38.0, 42.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",1); });
	timeline->AddAnimationClip(renderBoard, 42.0f, 42.3f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag", 0); });
	
	timeline->AddAnimationClip(renderBoard, 42.0f, 62.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",0); });
	timeline->AddAnimationClip(renderBoard, 62.0f,64.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",2); });
	timeline->AddAnimationClip(renderBoard, 64.0f, 66.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",0); });
		
}

