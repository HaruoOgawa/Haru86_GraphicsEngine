#include "App.h"
#include "./GameObject.h"
#include "./TimelineObject.h"
#include "./UIComponent.h"
#include "./RectTransformComponent.h"

GameObject* Haru86_Hexagon;
GameObject* Haru86_RaymarchHole;
GameObject* Haru86_MengerSponge;
GameObject* Haru86_polar_coordinate;
GameObject* Haru86_Ray;
GameObject* Haru86_PartyHole;

App::App()
{
	
}

App::~App() {

}
void App::Start() const {
	Haru86_Hexagon = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Haru86_Hexagon.frag");
	Haru86_RaymarchHole = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Haru86_RaymarchHole.frag");
	Haru86_MengerSponge = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Haru86_MengerSponge.frag");
	Haru86_polar_coordinate = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Haru86_polar_coordinate.frag");
	Haru86_Ray = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Haru86_Ray.frag");
	Haru86_PartyHole = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Haru86_PartyHole.frag");

	GameObject* uiButton = new GameObject(PrimitiveType::BOARD,"./Shader/UIStandard.vert","./Shader/UIStandard.frag");
	uiButton->SetScale(glm::vec3(0.1f,0.05f,1.0f));
	uiButton->AddComponent(new UIComponent(uiButton));
	uiButton->AddComponent(new RectTransformComponent(uiButton,0.1f,0.1f));
}
void App::Update() const {
	
}

void App::Timeline(TimelineObject* timeline) const {
	int iter = 0;
	float val = 3.0f;
	float startTime = 0.0f;
	float endTime = val;

	int maxClip = 180 / 6;
	for (auto i = 0; i < maxClip;i++) {
		switch (iter)
		{
		case 0:
			timeline->AddActivationClip(Haru86_Hexagon, startTime, endTime);
			break;
		case 1:
			timeline->AddActivationClip(Haru86_RaymarchHole, startTime, endTime);
			break;
		case 2:
			timeline->AddActivationClip(Haru86_MengerSponge, startTime, endTime);
			break;
		case 3:
			timeline->AddActivationClip(Haru86_polar_coordinate, startTime, endTime);
			break;
		case 4:
			timeline->AddActivationClip(Haru86_Ray, startTime, endTime);
			break;
		case 5:
			timeline->AddActivationClip(Haru86_PartyHole, startTime, endTime);
			break;
		default:
			break;
		}

		iter++;
		iter = iter % 6;
		startTime += val;
		endTime += val;
	}
}

