#include "GPGPUSample.h"
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

GPGPUSample::GPGPUSample(Object* o)
	: Component(o, static_cast<std::string>(typeid(GPGPUSample).name()).substr(6)),
	num(4096)
{
	//m_mesh = std::make_unique<Mesh>(PrimitiveType::BOARD);
	//owner->SetScale(glm::vec3(10.0, 10.0, 10.0));

	m_mesh = glTFLoader::Load("./Assets/Resources/glTFData/PhoenixWithVAT/Phoenix.gltf");
	
	m_material = std::make_unique<Material>(
		"./Assets/Shader/KuraShader/GPGPUTest.vert",
		"./Assets/Shader/KuraShader/GPGPUTest.geom",
		"./Assets/Shader/KuraShader/GPGPUTest.frag");

	//m_mainTex = std::make_unique<Texture>();
	m_posTex = std::make_unique<Texture>();
	m_normalTex = std::make_unique<Texture>();

	/*if (!m_mainTex->Load("./Assets/Resources/glTFData/PhoenixWithVAT/MainTex.png")) {
		printf("Cannot Load MainTex\n");
	}*/

	if (!m_posTex->Load("./Assets/Resources/glTFData/PhoenixWithVAT/PosTex.png")) {
		printf("Cannot Load PosTex\n");
	}

	if (!m_normalTex->Load("./Assets/Resources/glTFData/PhoenixWithVAT/NormalTex.png")) {
		printf("Cannot Load NormalTex\n");
	}

	Start();

}

GPGPUSample::~GPGPUSample() {

}

void GPGPUSample::Start() {
	m_computeBuffer = std::make_unique<ComputeBuffer>(sizeof(AttribData));
	std::vector<AttribData> sampleData(num, AttribData());
	m_computeBuffer->SetData<std::vector<AttribData>>(sampleData);

	m_computeShader = std::make_unique<ComputeShader>("./Assets/Shader/KuraShader/GPGPUTest.comp");
	m_computeShader->SetBuffer(m_computeBuffer.get(),m_material.get());

	sampleData.clear();
}

void GPGPUSample::Update() {
	m_computeShader->SetActive();
	m_computeShader->SetFloatUniform("_time", Game::GetInstance()->time);
	m_computeShader->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);
	m_computeShader->Dispatch(num/256,1,1);
}

void GPGPUSample::Draw() {
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

	m_posTex->SetActive();
	m_material->SetTexUniform("_PosTex", m_posTex->GetTextureID());

	m_normalTex->SetActive();
	m_material->SetTexUniform("_NormalTex", m_normalTex->GetTextureID());

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

void GPGPUSample::ProcessInput(const Uint8* state)const {

}