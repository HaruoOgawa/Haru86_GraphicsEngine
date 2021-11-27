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

#include <GL/glew.h>
#include <GL/glut.h>

#include <iostream>

GPGPUSample::GPGPUSample(Object* o)
	: Component(o, static_cast<std::string>(typeid(GPGPUSample).name()).substr(6)),
	num(8192)
{
	m_mesh = std::make_unique<Mesh>(PrimitiveType::BOARD);
	m_material = std::make_unique<Material>(
		"./Assets/Shader/KuraShader/GPGPUTest.vert",
		"./Assets/Shader/KuraShader/GPGPUTest.geom",
		"./Assets/Shader/KuraShader/GPGPUTest.frag");

	Start();
}

GPGPUSample::~GPGPUSample() {

}

void GPGPUSample::Start() {
	m_computeBuffer = std::make_unique<ComputeBuffer>(sizeof(AttribData) * num);
	std::vector<AttribData> sampleData(num, AttribData());
	m_computeBuffer->SetData<std::vector<AttribData>>(sampleData);

	m_computeShader = std::make_unique<ComputeShader>("./Assets/Shader/KuraShader/GPGPUTest.comp");
	m_computeShader->SetBuffer(m_computeBuffer.get(),m_material.get());

	sampleData.clear();
}

void GPGPUSample::Update() {
	m_computeShader->Dispatch(num/256,1,1);
}

void GPGPUSample::Draw() {
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

	m_material->SetActive();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	m_material->SetMatrixUniform("MVPMatrix", owner->transform->GetMVPMatrix());
	m_material->SetMatrixUniform("MMatrix", owner->transform->GetMMatrix());
	m_material->SetMatrixUniform("VMatrix", owner->transform->GetVMatrix());
	m_material->SetMatrixUniform("PMatrix", owner->transform->GetPMatrix());
	m_material->SetFloatUniform("_time", Game::GetInstance()->time);
	m_material->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);

	Graphics::DrawInstancedWithMesh(m_mesh.get(), 8192);

}

void GPGPUSample::ProcessInput(const Uint8* state)const {

}