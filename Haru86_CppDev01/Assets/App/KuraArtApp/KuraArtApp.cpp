#include "KuraArtApp.h"
#include "GraphicsEngine/Object/GameObject.h"
#include "GraphicsEngine/Object/TimelineObject.h"
#include "GraphicsEngine/Component/TimelineComponent.h"
#include "GraphicsEngine/Component/UIComponent.h"
#include "GraphicsEngine/Component/MeshRendererComponent.h"
#include "GraphicsEngine/Component/RectTransformComponent.h"
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/Object/AudioObject.h"
#include "GraphicsEngine/Component/AudioSourceComponent.h"
#include <memory>
#include <string>
#include "GraphicsEngine/Object/Object.h"
#include "./Assets/App/KuraArtApp/Script/KuraGPGPU.h"
#include "./Assets/App/KuraArtApp/Script/KuraTrail.h"
#include "GraphicsEngine/Object/CameraObject.h"

namespace Kura{
	std::unique_ptr<AudioObject> audioObj;
	std::unique_ptr<Object> gpgpu_obj;
	std::unique_ptr<CameraObject> camera_obj;
}

KuraArtApp::KuraArtApp()
{
	
}

KuraArtApp::~KuraArtApp() {

}

void KuraArtApp::Start() {
	Kura::camera_obj = std::make_unique<CameraObject>(CameraType::FIXED_CAMERA);
	Kura::camera_obj->SetPosition(glm::vec3(0, 0, -3.0));
	
	Kura::audioObj = std::make_unique<AudioObject>("./Assets/Resources/MusicData/n111.mp3");
	if (Kura::audioObj->Initialize()) {
		//Kura::audioObj->PlayAudio();
	}

	Kura::gpgpu_obj = std::make_unique<Object>();
	Kura::gpgpu_obj->AddComponent(new KuraGPGPU(Kura::gpgpu_obj.get()));
	Kura::gpgpu_obj->AddComponent(new KuraTrail(Kura::gpgpu_obj.get(),
		static_cast<KuraGPGPU*>(Kura::gpgpu_obj->GetComponent(static_cast<std::string>(typeid(KuraGPGPU).name())))
	));

}
void KuraArtApp::Update() {
	Kura::gpgpu_obj->Update();
}

void KuraArtApp::Draw() {
	static_cast<KuraGPGPU*>(Kura::gpgpu_obj->GetComponent(static_cast<std::string>(typeid(KuraGPGPU).name())))->Draw();
	static_cast<KuraTrail*>(Kura::gpgpu_obj->GetComponent(static_cast<std::string>(typeid(KuraTrail).name())))->Draw();
	
}

void KuraArtApp::Timeline(TimelineObject* timeline) {
	
}

