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
	
	//force////////////////////////////////////////////////////////////
	//force buffer
	m_computeBuffer_BoidsForce = std::make_unique<ComputeBuffer>(sizeof(BoidsResulrData) * num);
	std::vector<BoidsForceData> forceData(num, BoidsForceData());
	m_computeBuffer_BoidsForce->SetData<std::vector<BoidsForceData>>(forceData);
	//force compute
	m_computeShader_force = std::make_unique<ComputeShader>("./Assets/Shader/KuraShader/BoidsForce.comp");
	m_computeShader_force->SetBuffer(m_computeBuffer_BoidsForce.get(), 1, m_material.get());

	//result//////////////////////////////////////////////////////////
	//result buffer
	m_computeBuffer_BoidsResult = std::make_unique<ComputeBuffer>(sizeof(BoidsResulrData) * num);
	std::vector<BoidsResulrData> resultData(num, BoidsResulrData());
	m_computeBuffer_BoidsResult->SetData<std::vector<BoidsResulrData>>(resultData);
	//result compute
	m_computeShader_result = std::make_unique<ComputeShader>("./Assets/Shader/KuraShader/BoidsResult.comp");
	m_computeShader_result->SetBuffer(m_computeBuffer_BoidsResult.get(),0,m_material.get());
	/////////////////////////////////////////////////////////////////

	//clear data
	forceData.clear();
	resultData.clear();
}

void KuraGPGPU::Update() {
	//Dispatch force
	m_computeShader_force->SetActive();
	m_computeShader_force->SetFloatUniform("_time", Game::GetInstance()->time);
	m_computeShader_force->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);
	m_computeShader_force->Dispatch(num / 256, 1, 1);

	//Dispatch Result
	m_computeShader_result->SetActive();
	m_computeShader_result->SetFloatUniform("_time", Game::GetInstance()->time);
	m_computeShader_result->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);
	m_computeShader_result->Dispatch(num/256,1,1);
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