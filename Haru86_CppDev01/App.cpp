#include "App.h"
#include "./GameObject.h"
#include "./TimelineObject.h"
#include "./UIComponent.h"

GameObject* Haru86_Hexagon;
GameObject* Haru86_RaymarchHole;
GameObject* Haru86_Triangle;
GameObject* Haru86_MengerSponge;
GameObject* Haru86_Quaternion_Juria;
GameObject* Raymarching_domainID_samp;
GameObject* Haru86_polar_coordinate;
GameObject* Haru86_Ray;
GameObject* Haru86_PartyHole;

App::App()
{
	
}

App::~App() {

}
void App::Start() const {
	//Haru86_Hexagon = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Haru86_Hexagon.frag");
	//Haru86_RaymarchHole = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Haru86_RaymarchHole.frag");
	//‰ñ“] Haru86_Triangle = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Haru86_Triangle.frag");
	//Haru86_MengerSponge = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Haru86_MengerSponge.frag");
	//‰ñ“] Haru86_Quaternion_Juria = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Haru86_Quaternion_Juria.frag");
	//’¼i Raymarching_domainID_samp = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Raymarching_domainID_samp.frag");
	//Haru86_polar_coordinate = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Haru86_polar_coordinate.frag");
	//Haru86_Ray = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Haru86_Ray.frag");
	Haru86_PartyHole = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/Haru86_PartyHole.frag");

	
}
void App::Update() const {

}

void App::Timeline(TimelineObject* timeline) const {
	//timeline->AddActivationClip(Haru86_Hexagon, 0.0f, 3.0f);
	//timeline->AddActivationClip(Haru86_RaymarchHole, 3.0f, 6.0f);
}

