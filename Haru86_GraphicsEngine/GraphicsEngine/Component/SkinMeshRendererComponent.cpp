#include "SkinMeshRendererComponent.h"
#include "GraphicsEngine/Object/Object.h"
#include "GraphicsEngine/Object/CNode.h"
#include "GraphicsEngine/Component/Component.h"
#include "GraphicsEngine/Component/TransformComponent.h"
#include "GraphicsEngine/Graphics/glTFLoader.h"
#include "GraphicsEngine/Graphics/glTFData.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/GraphicsMain/GraphicsMain.h"
#include "GraphicsEngine/Object/CameraObject.h"
#include "GraphicsEngine/Animation/Skeleton.h"
#include "GraphicsEngine/Animation/Pose.h"
#include "GraphicsEngine/Message/Console.h"

SkinMeshRendererComponent::SkinMeshRendererComponent(Object* o, std::string objPath, std::string vertexShaderName, std::string fragmentShaderName) :
	ARendererComponent(o)
{
	useZTest = true;
	std::shared_ptr<gltf::glTFData> data = gltf::glTFLoader::Load(objPath);
	mesh = data->GetMesh();
	mesh->glDrawType = GLDrawType::NONE;

	m_Skeleton = data->GetSkeleton();
	m_CurrentPose = m_Skeleton->GetRestPose();
	m_CurrentPose->GetMatrixPalette(m_PoseMatrix);

	material = std::make_shared<Material>(vertexShaderName, fragmentShaderName);
}

SkinMeshRendererComponent::~SkinMeshRendererComponent() {

}

void SkinMeshRendererComponent::Update() {
	//Console::Log("SkinMeshRendererComponent::Update\n");
	// アニメーションの更新

}

void SkinMeshRendererComponent::Draw() {
	if (useZTest == true) {
		glEnable(GL_DEPTH_TEST);
	}
	else if (useZTest == false) {
		glDisable(GL_DEPTH_TEST);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	material->SetActive();
	material->SetMatrixUniform("MVPMatrix", owner->GetRootNode()->GetComponent<TransformComponent>()->GetMVPMatrix());
	material->SetMatrixUniform("MMatrix", owner->GetRootNode()->GetComponent<TransformComponent>()->GetMMatrix());
	material->SetMatrixUniform("VMatrix", owner->GetRootNode()->GetComponent<TransformComponent>()->GetVMatrix());
	material->SetMatrixUniform("PMatrix", owner->GetRootNode()->GetComponent<TransformComponent>()->GetPMatrix());
	material->SetFloatUniform("_time", game->time);
	material->SetFloatUniform("_deltaTime", game->deltaTime);
	material->SetVec2Uniform("_resolution", GraphicsRenderer::GetInstance()->GetScreenSize());
	material->SetVec3Uniform("_CameraPos", GraphicsMain::GetInstance()->game_camera_instance->GetPosition());

	// skin mesh uniform
	material->SetMatrixVectorUniform("pose", m_PoseMatrix);
	material->SetMatrixVectorUniform("invBindPose", m_Skeleton->GetInvBindPose());

	//
	mesh->Draw();
}

void SkinMeshRendererComponent::ProcessInput(const SDL_Event& e) {

}