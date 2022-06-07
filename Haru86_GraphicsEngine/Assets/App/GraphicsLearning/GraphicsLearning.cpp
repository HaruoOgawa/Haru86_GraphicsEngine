#include "GraphicsLearning.h"
#include "GraphicsEngine/Object/GameObject.h"
#include "GraphicsEngine/Component/TransformComponent.h"
#include "GraphicsEngine/Object/CameraObject.h"
#include "GraphicsEngine/Component/CameraComponent.h"
#include "GraphicsEngine/Object/CNode.h"
#include "GraphicsEngine/Component/MeshRendererComponent.h"
GraphicsLearning::GraphicsLearning() {

}

GraphicsLearning::~GraphicsLearning() {

}

void GraphicsLearning::Start() {
	//
	cam_obj = std::make_shared<CameraObject>(CameraType::FIXED_CAMERA);
	cam_obj->m_cameraComponent->cameraCenter = glm::vec3(0.0, -1.0, 0.0);
	GraphicsMain::GetInstance()->game_camera_instance = cam_obj;
	cam_obj->GetRootNode()->GetComponent<TransformComponent>()->SetPosition(glm::vec3(8.5, 2.0, 8.5));

	//
	GraphicsRenderer::GetInstance()->SetBackgroudColor(glm::vec4(glm::vec3(1.0f), 1.0));
	m_GraphObj = std::make_shared<GameObject>("Assets/Resources/glTFData/Dragon_1/Dragon_1.gltf");
	m_GraphObj->SetScale(glm::vec3(0.5f));

	//
	/*m_CubeMapObj = std::make_shared<GameObject>(PrimitiveType::CUBE,
		"./Assets/Shader/KuraShader/Background.vert",
		"./Assets/Shader/KuraShader/Background.frag");
	m_CubeMapObj->SetScale(glm::vec3(1000.0f));
	std::vector<std::string> texPath = { "./Assets/Resources/TextureData/InkBackground.png" };
	std::vector<std::string> texUniformName = { "_backgroundTex" };
	m_CubeMapObj->meshComp->GetMaterial()->LoadTextureList(texPath, texUniformName);*/
}

void GraphicsLearning::Update() {

}

void GraphicsLearning::Draw() {

}

void GraphicsLearning::Timeline(class TimelineObject* timelineObj) {

}