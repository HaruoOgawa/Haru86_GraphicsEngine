#include "KuraArtApp.h"
#include "GraphicsEngine/Object/GameObject.h"
#include "GraphicsEngine/Object/TimelineObject.h"
#include "GraphicsEngine/Component/TimelineComponent.h"
#include "GraphicsEngine/Component/UIComponent.h"
#include "GraphicsEngine/Component/MeshRendererComponent.h"
#include "GraphicsEngine/Component/RectTransformComponent.h"
#include "GraphicsEngine/Graphics/Material.h"

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
	Kura::Scene3_Frag = new GameObject(PrimitiveType::BOARD, "./Assets/Shader/demo.vert", "./Assets/Shader/VedaStructuredShader/scene3.frag");
	Kura::renderBoard = new GameObject(PrimitiveType::BOARD, "./Assets/Shader/VedaStructuredShader/BoardRender.vert", "./Assets/Shader/VedaStructuredShader/BoardRender.frag", RenderType::FrameBuffer);

}
void KuraArtApp::Update() {

}


void KuraArtApp::Timeline(TimelineObject* timeline) {
	
}

