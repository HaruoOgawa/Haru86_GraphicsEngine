#include "KuraArtApp.h"

#include "../../Object/GameObject.h"
#include "../../Object/TimelineObject.h"
#include "../../Component/TimelineComponent.h"
#include "../../Component/UIComponent.h"
#include "../../Component/RectTransformComponent.h"
#include "../../Component/MeshRendererComponent.h"
#include "../../Graphics/Material.h"

namespace Kura{
	GameObject* Scene3_Frag;
	GameObject* renderBoard;
}


KuraArtApp::KuraArtApp()
{

}

KuraArtApp::~KuraArtApp() {

}
void KuraArtApp::Start() {
	Kura::Scene3_Frag = new GameObject(PrimitiveType::BOARD, "./Shader/demo.vert", "./Shader/VedaStructuredShader/scene3.frag");
	Kura::renderBoard = new GameObject(PrimitiveType::BOARD, "./Shader/VedaStructuredShader/BoardRender.vert", "./Shader/VedaStructuredShader/BoardRender.frag", RenderType::FrameBuffer);

}
void KuraArtApp::Update() {

}


void KuraArtApp::Timeline(TimelineObject* timeline) {
	
}

