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
	//force=0 data=1

	//force buffer
	m_computeBuffer_BoidsForce = std::make_unique<ComputeBuffer>(sizeof(BoidsForce) * num);
	std::vector<BoidsForce> forceData(num, BoidsForce());
	m_computeBuffer_BoidsForce->SetData<std::vector<BoidsForce>>(forceData);
	
	//data buffer
	m_computeBuffer_BoidsData = std::make_unique<ComputeBuffer>(sizeof(BoidsData) * num);
	std::vector<BoidsData> resultData(num, BoidsData());
	m_computeBuffer_BoidsData->SetData<std::vector<BoidsData>>(resultData);
	
	//SetBuffer//////////////
	//force compute
	m_computeShader_force = std::make_unique<ComputeShader>("./Assets/Shader/KuraShader/BoidsForce.comp");
	m_computeShader_force->SetBuffer(m_computeBuffer_BoidsForce.get(), 0, m_material.get());
	m_computeShader_force->SetBuffer(m_computeBuffer_BoidsData.get(), 1, m_material.get());

	//data compute
	m_computeShader_data = std::make_unique<ComputeShader>("./Assets/Shader/KuraShader/BoidsData.comp");
	m_computeShader_data->SetBuffer(m_computeBuffer_BoidsForce.get(),0,m_material.get());
	m_computeShader_data->SetBuffer(m_computeBuffer_BoidsData.get(),1,m_material.get());
	
	//set buffer to material
	m_material->SetBuffer(m_computeBuffer_BoidsForce.get(), 0);
	m_material->SetBuffer(m_computeBuffer_BoidsData.get(), 1);

	//clear data
	forceData.clear();
	resultData.clear();

}

void KuraGPGPU::Update() {
	//Dispatch force///////////////////////////
	m_computeShader_force->SetActive();
	m_computeShader_force->SetFloatUniform("_time", Game::GetInstance()->time);
	m_computeShader_force->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);
	//boid uniform
	m_computeShader_force->SetIntUniform("_boids_count", num);
	m_computeShader_force->SetFloatUniform("_maxBoidsDist", 50);
	m_computeShader_force->SetFloatUniform("_maxBoidsField",400);
	m_computeShader_force->SetFloatUniform("_centerPosPower", 1000000.0);
	m_computeShader_force->SetFloatUniform("_NoiseValue", 0.1);
	//ŽÀÛ‚ÉŽg‚Á‚Ä‚¢‚éuniform
	m_computeShader_force->SetFloatUniform("_joinPower", 1000);
	m_computeShader_force->SetFloatUniform("_separatePower", 10);
	m_computeShader_force->SetFloatUniform("_alignmentPower", 10);
	m_computeShader_force->SetFloatUniform("_joinDisMin", 100);
	m_computeShader_force->SetFloatUniform("_separateDistMin", 10);
	m_computeShader_force->SetFloatUniform("_alignmentDistMin", 250);
	m_computeShader_force->Dispatch(num / 256, 1, 1);

	//Dispatch Data///////////////
	m_computeShader_data->SetActive();
	m_computeShader_data->SetFloatUniform("_time", Game::GetInstance()->time);
	m_computeShader_data->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);
	//boid uniform
	/*m_computeShader_data->SetIntUniform("_boids_count", num);
	m_computeShader_data->SetFloatUniform("_maxBoidsDist", 50);
	m_computeShader_data->SetFloatUniform("_maxBoidsField", 400);
	m_computeShader_data->SetFloatUniform("_centerPosPower", 1000000.0);
	m_computeShader_data->SetFloatUniform("_NoiseValue", 0.1);
	m_computeShader_data->SetFloatUniform("_joinPower", 10);
	m_computeShader_data->SetFloatUniform("_separatePower", 10);
	m_computeShader_data->SetFloatUniform("_alignmentPower", 10);
	m_computeShader_data->SetFloatUniform("_joinDisMin", 100);
	m_computeShader_data->SetFloatUniform("_separateDistMin", 10);
	m_computeShader_data->SetFloatUniform("_alignmentDistMin", 250);*/
	m_computeShader_data->Dispatch(num/256,1,1);
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
	
	Graphics::DrawInstancedWithMesh(m_mesh.get(), num,m_material.get());

}

void KuraGPGPU::ProcessInput(const Uint8* state)const {

}