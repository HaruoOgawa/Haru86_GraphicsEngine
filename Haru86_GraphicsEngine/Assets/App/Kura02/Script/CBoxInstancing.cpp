#include "CBoxInstancing.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/Graphics/Graphics.h"
#include <GL/glew.h>
#include "GraphicsEngine/Component/TransformComponent.h"
#include "GraphicsEngine/Object/CameraObject.h"
#include "GraphicsEngine/Graphics/ComputeBuffer.h"

CBoxInstancing::CBoxInstancing(Object* o)
	: Component(o, static_cast<std::string>(typeid(CBoxInstancing).name()).substr(6)),
	instanciedCound(124*124),
	sideCubeCount(124)
{
	Start();
}

CBoxInstancing::~CBoxInstancing() {
}

void CBoxInstancing::Start() {
	owner->transform->scale = glm::vec3(1.0);
	m_mesh = std::make_shared<Mesh>(PrimitiveType::CUBE);
	m_material = std::make_shared<Material>(
		"./Assets/Shader/Kura02/InstancedBox.vert",
		"./Assets/Shader/Kura02/InstancedBox.frag"
	);
	
	m_cubeGroundBuffer = std::make_shared<ComputeBuffer>(sizeof(SCubeFieldObj)*instanciedCound);
	std::vector<SCubeFieldObj> init_CubeFieldObj;
	for (int y = 0; y < sideCubeCount;y++) {
		for (int x = 0; x < sideCubeCount; x++) {
			SCubeFieldObj obj(x,y,x+y*sideCubeCount);
		}
	}
	m_cubeGroundBuffer->SetData<std::vector<SCubeFieldObj>>(init_CubeFieldObj);

	//set buffer to material
	m_material->SetBuffer(m_cubeGroundBuffer, 0);
}

void CBoxInstancing::Update() {

}

void CBoxInstancing::Draw() {
	owner->transform->CalMatrix();
	m_material->SetActive();
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_BLEND_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_material->SetMatrixUniform("MVPMatrix", owner->transform->GetMVPMatrix() ); //
	m_material->SetMatrixUniform("MMatrix", owner->transform->GetMMatrix());
	m_material->SetMatrixUniform("VMatrix", owner->transform->GetVMatrix());
	m_material->SetMatrixUniform("PMatrix", owner->transform->GetPMatrix());
	m_material->SetFloatUniform("_time", Game::GetInstance()->time);
	m_material->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);
	m_material->SetVec3Uniform("_CameraPosition", Game::GetInstance()->game_camera_instance->GetPosition());
	m_material->SetIntUniform("_instancedCound", instanciedCound);
	m_material->SetIntUniform("_sideCubeCount", sideCubeCount);
	m_material->SetFloatUniform("_cubeWidth", 1.0);
	m_material->SetVec3Uniform("_lightDir", glm::vec3(-2.0, 1.0, 1.0));
	Graphics::DrawInstancedWithMesh(m_mesh, instanciedCound, m_material,GL_TRIANGLES);
	
}

void CBoxInstancing::ProcessInput(const Uint8* state)const {

}