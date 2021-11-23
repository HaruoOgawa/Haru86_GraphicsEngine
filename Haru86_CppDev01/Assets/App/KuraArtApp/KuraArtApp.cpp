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

namespace Kura{
	GameObject* Scene3_Frag;
	GameObject* renderBoard;
	std::unique_ptr<AudioObject> audioObj;
}

KuraArtApp::KuraArtApp()
{

}

KuraArtApp::~KuraArtApp() {

}
void KuraArtApp::Start() {
	Kura::audioObj = std::make_unique<AudioObject>("./Assets/Resources/MusicData/n111.mp3");
	if (Kura::audioObj->Initialize()) {
		Kura::audioObj->PlayAudio();
	}

	Kura::Scene3_Frag = new GameObject(PrimitiveType::BOARD, "./Assets/Shader/demo.vert", "./Assets/Shader/VedaStructuredShader/scene3.frag");
	Kura::renderBoard = new GameObject(PrimitiveType::BOARD, "./Assets/Shader/VedaStructuredShader/BoardRender.vert", "./Assets/Shader/VedaStructuredShader/BoardRender.frag", RenderType::FrameBuffer);

}
void KuraArtApp::Update() {
	static_cast<AudioSourceComponent*>(Kura::audioObj->audioSource)->Update();
}


void KuraArtApp::Timeline(TimelineObject* timeline) {
	
}

