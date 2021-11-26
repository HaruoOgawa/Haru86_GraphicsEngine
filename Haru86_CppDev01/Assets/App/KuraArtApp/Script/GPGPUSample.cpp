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

GPGPUSample::GPGPUSample(Object* o)
	: Component(o, static_cast<std::string>(typeid(GPGPUSample).name()).substr(6)),
	num(1024)
{
	m_mesh = std::make_unique<Mesh>(PrimitiveType::BOARD);
	m_material = std::make_unique<Material>(
		"./Assets/Shader/KuraShader/GPGPUTest.vert",
		"./Assets/Shader/KuraShader/GPGPUTest.frag");

	Start();
}

GPGPUSample::~GPGPUSample() {

}

void GPGPUSample::Start() {
	m_computeBuffer = std::make_unique<ComputeBuffer>(sizeof(float) * num);
	std::vector<AttribData> sampleData(num, AttribData());
	m_computeBuffer->SetData<std::vector<AttribData>>(sampleData);

	m_computeShader = std::make_unique<ComputeShader>("./Assets/Shader/KuraShader/GPGPUTest.comp");
	m_computeShader->SetBuffer(m_computeBuffer.get());

	sampleData.clear();
}

void GPGPUSample::Update() {
	m_computeShader->Dispatch(num/256,1,1);
	
	std::unique_ptr<AttribData> sampleData=std::make_unique<AttribData>();
	m_computeBuffer->GetBufferData<AttribData>(sampleData.get(),0);
	printf("BufferNum is x:%f,y:%f,z:%f,w:%f \n",sampleData.get()->velocity[0], sampleData.get()->velocity[1], sampleData.get()->velocity[2], sampleData.get()->velocity[3]);

}

void GPGPUSample::Draw() {
	glMemoryBarrier(GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

	m_computeShader->BindComputeBuffer(CorrectionType::ARRAY);

	m_material->SetActive();
	//Œã‚ÅUniform‚ðƒZƒbƒg‚·‚é
	m_material->SetMatrixUniform("MVPMatrix", owner->transform->GetMVPMatrix());
	m_material->SetMatrixUniform("MMatrix", owner->transform->GetMMatrix());
	m_material->SetMatrixUniform("VMatrix", owner->transform->GetVMatrix());
	m_material->SetMatrixUniform("PMatrix", owner->transform->GetPMatrix());
	m_material->SetFloatUniform("_time", Game::GetInstance()->time);
	m_material->SetFloatUniform("_deltaTime", Game::GetInstance()->deltaTime);

	Graphics::DrawInstancedWithMesh(m_mesh.get(), 1024);

	m_computeShader->DisBindComputeBuffer(CorrectionType::ARRAY);
}

void GPGPUSample::ProcessInput(const Uint8* state)const {

}