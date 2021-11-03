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
GameObject* Scene3_Frag;
GameObject* Scene4_Frag;
GameObject* Scene5_Frag;

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
	Scene3_Frag = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/VedaStructuredShader/scene3.frag");
	Scene4_Frag = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/VedaStructuredShader/scene4.frag");
	Scene5_Frag = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/VedaStructuredShader/scene5.frag");


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
	//Ray Activation
	
	timeline->AddActivationClip(Scene1_Frag,0.0f,42.0f);
	timeline->AddActivationClip(Scene2_Frag, 42.0f, 64.0f);
	timeline->AddActivationClip(Scene3_Frag, 64.0f, 85.0f);
	//-14.0f
	timeline->AddActivationClip(Scene4_Frag, 85.0f, 128.0f - 12.0f);
	timeline->AddActivationClip(Scene5_Frag, 128.0f - 12.0f, 146.0f-20.0f);
	timeline->AddActivationClip(Scene1_Frag, 126.0f, 157.0f);
	//146.0f - 20.0f=126.0f, 179.0f - 22.0f=157.0f
	
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
		[](float val) {
			//gamept->GetInstance()->animTime += gamept->GetInstance()->deltaTime;
			Scene1_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 3);
			Scene1_Frag->meshComp->material->SetFloatUniform("_cameraMoveVal", val);
			

	});
	
	timeline->AddAnimationClip(Scene1_Frag, 42.0f, 42.5f,
		[](float val) {
			//gamept->GetInstance()->animTime += gamept->GetInstance()->deltaTime;
			Scene1_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 0);
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
	
	startTime = 64.0f;
	endTime = startTime + 3.0;

	for (int i = 0; i < 8;i++) {
		int val = i % 3;
		switch (val) {
		case 0:
			timeline->AddAnimationClip(Scene3_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [](float val) {Scene3_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 0.0); });
			break;
		case 1:
			timeline->AddAnimationClip(Scene3_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [] (float val){Scene3_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 1.0); });
			break;
		case 2:
			timeline->AddAnimationClip(Scene3_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [](float val) {Scene3_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 2.0); });
			break;
		default:
			break;

		}
	}
	
	startTime = 85.0f;
	endTime = startTime + 3.0;

	for (int i = 0; i < 11;i++) {
		int val = i % 3;
		switch (val) {
		case 0:
			timeline->AddAnimationClip(Scene4_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [](float val) {Scene4_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 0.0); });
			break;
		case 1:
			timeline->AddAnimationClip(Scene4_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [] (float val){Scene4_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 1.0); });
			break;
		case 2:
			timeline->AddAnimationClip(Scene4_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [](float val) {Scene4_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 2.0); });
			break;
		default:
			break;

		}
	}
	
	startTime = 128.0f - 12.0f;
	endTime = startTime + 3.0;

	for (int i = 0; i < 5;i++) {
		int val = i % 3;
		switch (val) {
		case 0:
			timeline->AddAnimationClip(Scene5_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [](float val) {Scene5_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 0.0); });
			break;
		case 1:
			timeline->AddAnimationClip(Scene5_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [] (float val){Scene5_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 1.0); });
			break;
		case 2:
			timeline->AddAnimationClip(Scene5_Frag, static_cast<float>(startTime + 3.0 * i), static_cast<float>(endTime + 3.0 * i), [](float val) {Scene5_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 2.0); });
			break;
		default:
			break;

		}
	}


	timeline->AddAnimationClip(Scene2_Frag, static_cast<float>(57), static_cast<float>(64.0), [](float val) {Scene2_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 0);  });

	timeline->AddAnimationClip(Scene4_Frag, 85.0, 106.5 - 1.0f, [](float val) {Scene4_Frag->meshComp->material->SetFloatUniform("isTransform",0.0f); });
	timeline->AddAnimationClip(Scene4_Frag, 106.5 - 1.0f, 128.0f - 12.0f, [](float val) {Scene4_Frag->meshComp->material->SetFloatUniform("isTransform",1.0f); });

	timeline->AddAnimationClip(Scene1_Frag, 146.0f - 20.0f, 146.2f - 20.0f,
		[](float val) {
		//gamept->GetInstance()->animTime += gamept->GetInstance()->deltaTime;
		Scene1_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 0);
		Scene1_Frag->meshComp->material->SetFloatUniform("_cameraMoveVal", val);
	});

	timeline->AddAnimationClip(Scene1_Frag, 126.0f, 157.0f,
		[](float val) {
		//gamept->GetInstance()->animTime += gamept->GetInstance()->deltaTime;
		Scene1_Frag->meshComp->material->SetFloatUniform("_cameraPositionIndex", 4);
		Scene1_Frag->meshComp->material->SetFloatUniform("_cameraMoveVal", val);
	});



	//font/////////////////////////////////

	//FirstText
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
	
	//finalText
	//  126.0f, 157.0f
	timeline->AddActivationClip(DemoText, 126.0f, 126.0f+10.0);
	timeline->AddActivationClip(MusicText, 126.0f + 10.0, 126.0f + 20.0);
	timeline->AddActivationClip(MyCreditText, 126.0f + 20.0, 126.0f + 30.0);
	
	timeline->AddAnimationClip(DemoText, 126.0f, 126.0f + 10.0, [](float val) {

		//printf("val: %f \n", val);
		DemoText->meshComp->material->SetFloatUniform("_ColorIndex", 1.0f);

		float delayVal = 0.2f;
		if (val <= delayVal) {
			DemoText->meshComp->material->SetFloatUniform("_alpha", val / delayVal);
		}
		else if (val > delayVal && val < 1.0f - delayVal) {
			DemoText->meshComp->material->SetFloatUniform("_alpha", 1.0f);
		}
		else if (val >= 1.0f - delayVal) {
			DemoText->meshComp->material->SetFloatUniform("_alpha", (1.0f - val) / delayVal);
		}

	});

	timeline->AddAnimationClip(MusicText, 126.0f + 10.0, 126.0f + 20.0, [](float val) {

		//printf("val: %f \n", val);
		DemoText->meshComp->material->SetFloatUniform("_ColorIndex", 1.0f);

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
	timeline->AddAnimationClip(MyCreditText, 126.0f + 20.0, 126.0f + 30.0, [](float val) {

		//printf("val: %f \n", val);
		DemoText->meshComp->material->SetFloatUniform("_ColorIndex", 1.0f);

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
	

	//PostProcess
	timeline->AddAnimationClip(renderBoard, 0.0f, 38.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",0); });
	timeline->AddAnimationClip(renderBoard, 38.0, 42.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",1); });
	timeline->AddAnimationClip(renderBoard, 42.0f, 42.3f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag", 0); });
	
	timeline->AddAnimationClip(renderBoard, 42.0f, 62.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",0); });
	timeline->AddAnimationClip(renderBoard, 62.0f,65.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",2); });
	timeline->AddAnimationClip(renderBoard, 65.0f, 66.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag", 0); });
	
	timeline->AddAnimationClip(renderBoard, 84.0f, 84.5f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",0); });
	timeline->AddAnimationClip(renderBoard, 84.5f,85.5f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",2); });
	timeline->AddAnimationClip(renderBoard, 85.5f, 86.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",0); });
	
	timeline->AddAnimationClip(renderBoard, 102.0, 102.5, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag", 0); });
	timeline->AddAnimationClip(renderBoard, 102.5, 104.5, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag", 5); });
	timeline->AddAnimationClip(renderBoard, 104.5, 105.5, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag", 0); });

	//timeline->AddAnimationClip(renderBoard, 85.0, 106.5 - 1.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",0); });
	timeline->AddAnimationClip(renderBoard, 106.5 - 1.0f, 128.0f - 12.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",4); });
	timeline->AddAnimationClip(renderBoard, 128.0f - 12.0f, 128.5f - 12.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",0); });
	
	timeline->AddAnimationClip(renderBoard, 125.5f, 126.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",0); });
	timeline->AddAnimationClip(renderBoard, 126.0f, 157.0f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",3); });
	timeline->AddAnimationClip(renderBoard, 157.0f, 157.5f, [](float val) {renderBoard->meshComp->material->SetFloatUniform("_postProcessFlag",0); });
		
}

