#include "CBoxInstancing.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/Graphics/Graphics.h"
#include <GL/glew.h>
#include "GraphicsEngine/Component/TransformComponent.h"
#include "GraphicsEngine/Object/CameraObject.h"

CBoxInstancing::CBoxInstancing(Object* o)
	: Component(o, static_cast<std::string>(typeid(CBoxInstancing).name()).substr(6))
{
	Start();
}

CBoxInstancing::~CBoxInstancing() {
}

void CBoxInstancing::Start() {
	owner->transform->scale = glm::vec3(1.0);
	m_mesh = std::make_shared<Mesh>(PrimitiveType::CUBE);
	m_material = std::make_shared<Material>(
		"./Assets/Shader/CreativeCoding20220108/InstancedBox.vert",
		"./Assets/Shader/CreativeCoding20220108/InstancedBox.frag"
	);
}

void CBoxInstancing::Update() {

}

void CBoxInstancing::Draw() {
	owner->transform->CalMatrix();
	m_material->SetActive();
	m_material->SetMatrixUniform("MVPMatrix", owner->transform->GetMVPMatrix() ); //
	m_material->SetMatrixUniform("MMatrix", owner->transform->GetMMatrix());
	m_material->SetMatrixUniform("VMatrix", owner->transform->GetVMatrix());
	m_material->SetMatrixUniform("PMatrix", owner->transform->GetPMatrix());
	m_material->SetFloatUniform("_time", Game::GetInstance()->time);
	m_material->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);
	m_material->SetVec3Uniform("_CameraPosition", Game::GetInstance()->game_camera_instance->GetPosition());
	Graphics::DrawInstancedWithMesh(m_mesh, 256, m_material,GL_TRIANGLES);
	
}

void CBoxInstancing::ProcessInput(const Uint8* state)const {

}