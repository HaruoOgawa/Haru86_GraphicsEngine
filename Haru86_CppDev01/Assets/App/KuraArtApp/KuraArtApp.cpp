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
#include "./Assets/App/KuraArtApp/Script/GPGPUSample.h"

namespace Kura{
	std::unique_ptr<AudioObject> audioObj;
	std::unique_ptr<Object> gpgpu_obj;
}

KuraArtApp::KuraArtApp()
{

}

KuraArtApp::~KuraArtApp() {

}

//ÉJÉÅÉâÇÃéÊÇËàµÇ¢Ç…Ç¬Ç¢Çƒã≠âªÇ∑ÇÈïKóvÇ™Ç†ÇÈ

void KuraArtApp::Start() {
	Kura::audioObj = std::make_unique<AudioObject>("./Assets/Resources/MusicData/n111.mp3");
	if (Kura::audioObj->Initialize()) {
		Kura::audioObj->PlayAudio();
	}

	Kura::gpgpu_obj = std::make_unique<Object>();
	Kura::gpgpu_obj->AddComponent(new GPGPUSample(Kura::gpgpu_obj.get()));


}
void KuraArtApp::Update() {
	static_cast<AudioSourceComponent*>(Kura::audioObj->audioSource)->Update();
}


void KuraArtApp::Timeline(TimelineObject* timeline) {
	
}

