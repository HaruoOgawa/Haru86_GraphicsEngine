#include "RaymarchingObject.h"
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Game/Game.h"
#include "GraphicsEngine/Component/TransformComponent.h"

RaymarchingObject::RaymarchingObject(std::string fragmentShaderName)
	: Object()
{
	m_material = std::make_shared<Material>("./Assets/Shader/RaymarchingObject.vert",fragmentShaderName,RenderingSurfaceType::RAYMARCHING);
	m_mesh = std::make_shared<Mesh>(PrimitiveType::BOARD);
}

RaymarchingObject::~RaymarchingObject() {

}

void RaymarchingObject::Start() {

}

void RaymarchingObject::Update() {

}

void RaymarchingObject::Draw() {
	m_material->SetActive();
	m_material->SetMatrixUniform("MVPMatrix", transform->GetMVPMatrix());
	m_material->SetMatrixUniform("MMatrix", transform->GetMMatrix());
	m_material->SetMatrixUniform("VMatrix", transform->GetVMatrix());
	m_material->SetMatrixUniform("PMatrix", transform->GetPMatrix());
	m_material->SetFloatUniform("_time", Game::GetInstance()->time);
	m_material->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);
	m_material->SetVec2Uniform("_resolution", GameRenderer::GetInstance()->GetScreenSize());
	m_material->SetFloatUniform("_frameResolusion", GameRenderer::GetInstance()->frameResolusion);

	m_mesh->Draw();
}