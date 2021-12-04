#include "KuraGPGPU.h"
#include <string>
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Graphics/Graphics.h"
#include "GraphicsEngine/Object/Object.h"
#include "GraphicsEngine/Component/TransformComponent.h"
#include "GraphicsEngine/Game/Game.h"
#include "../KuraArtApp.h"
#include "GraphicsEngine/Graphics/ComputeBuffer.h"
#include "GraphicsEngine/Graphics/ComputeShader.h"
#include <vector>
#include "GraphicsEngine/Graphics/glTFLoader.h"

#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "GraphicsEngine/Graphics/Texture.h"

KuraGPGPU::KuraGPGPU(Object* o)
	: Component(o, static_cast<std::string>(typeid(KuraGPGPU).name()).substr(6)),
	num(4096)
{
	//m_mesh = std::make_unique<Mesh>(PrimitiveType::BOARD);
	//owner->SetScale(glm::vec3(10.0, 10.0, 10.0));

	m_mesh = glTFLoader::Load("./Assets/Resources/glTFData/PhoenixWithVAT/Phoenix.gltf");

	m_material = std::make_unique<Material>(
		"./Assets/Shader/KuraShader/BoidsResult.vert",
		"./Assets/Shader/KuraShader/BoidsResult.geom",
		"./Assets/Shader/KuraShader/BoidsResult.frag");

	Start();

}

KuraGPGPU::~KuraGPGPU() {

}

void KuraGPGPU::Start() {
	m_computeBuffer = std::make_unique<ComputeBuffer>(sizeof(AttribData) * num);
	std::vector<AttribData> sampleData(num, AttribData());
	m_computeBuffer->SetData<std::vector<AttribData>>(sampleData);

	m_computeShader = std::make_unique<ComputeShader>("./Assets/Shader/KuraShader/BoidsResult.comp");
	m_computeShader->SetBuffer(m_computeBuffer.get(),m_material.get());

	sampleData.clear();
}

void KuraGPGPU::Update() {
	m_computeShader->SetActive();
	m_computeShader->SetFloatUniform("_time", Game::GetInstance()->time);
	m_computeShader->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);
	m_computeShader->Dispatch(num/256,1,1);
}

void KuraGPGPU::Draw() {
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

	m_material->SetActive();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	m_material->SetMatrixUniform("MVPMatrix", owner->transform->GetMVPMatrix() * m_mesh->localMatrix); //
	m_material->SetMatrixUniform("MMatrix", owner->transform->GetMMatrix());
	m_material->SetMatrixUniform("VMatrix", owner->transform->GetVMatrix());
	m_material->SetMatrixUniform("PMatrix", owner->transform->GetPMatrix());
	m_material->SetFloatUniform("_time", Game::GetInstance()->time);
	m_material->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);
	
	

	Graphics::DrawInstancedWithMesh(m_mesh.get(), 4096,m_material.get());

}

void KuraGPGPU::ProcessInput(const Uint8* state)const {

}