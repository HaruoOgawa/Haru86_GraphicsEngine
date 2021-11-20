#include "KuraArtApp.h"

#include "../../GameObject.h"
#include "../../TimelineObject.h"
#include "../../TimelineComponent.h"
#include "../../UIComponent.h"
#include "../../RectTransformComponent.h"
#include "../../MeshRendererComponent.h"
#include "../../Material.h"

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

