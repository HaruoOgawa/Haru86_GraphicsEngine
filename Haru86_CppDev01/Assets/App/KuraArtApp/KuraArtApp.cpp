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
#include "GraphicsEngine/Object/CameraObject.h"

namespace Kura{
	std::unique_ptr<AudioObject> audioObj;
	//std::unique_ptr<GameObject> testObj;
	std::unique_ptr<Object> gpgpu_obj;
	std::unique_ptr<CameraObject> camera_obj;
}

KuraArtApp::KuraArtApp()
{
	
}

KuraArtApp::~KuraArtApp() {

}

//ÉJÉÅÉâÇÃéÊÇËàµÇ¢Ç…Ç¬Ç¢Çƒã≠âªÇ∑ÇÈïKóvÇ™Ç†ÇÈ

void KuraArtApp::Start() {
	Kura::camera_obj = std::make_unique<CameraObject>(CameraType::FIXED_CAMERA);
	Kura::camera_obj->SetPosition(glm::vec3(0, 0, -3.0));
	
	Kura::audioObj = std::make_unique<AudioObject>("./Assets/Resources/MusicData/n111.mp3");
	if (Kura::audioObj->Initialize()) {
		Kura::audioObj->PlayAudio();
	}

	//Kura::testObj = std::make_unique<GameObject>(PrimitiveType::BOARD);
	//Kura::testObj = std::make_unique<GameObject>("./Assets/Resources/glTFData/Phoenix_Blender/Phoenix.gltf");

	Kura::gpgpu_obj = std::make_unique<Object>();
	Kura::gpgpu_obj->AddComponent(new KuraGPGPU(Kura::gpgpu_obj.get()));


}
void KuraArtApp::Update() {
	static_cast<AudioSourceComponent*>(Kura::audioObj->audioSource)->Update();
	Kura::gpgpu_obj->Update();
	//Kura::testObj->Update();
}

void KuraArtApp::Draw() {
	
	static_cast<KuraGPGPU*>(Kura::gpgpu_obj->GetComponent(static_cast<std::string>(typeid(KuraGPGPU).name())))->Draw();
	//Kura::testObj->meshComp->Draw();
}

void KuraArtApp::Timeline(TimelineObject* timeline) {
	
}

