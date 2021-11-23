#include "GPGPUSample.h"
#include <string>
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Graphics/Graphics.h"

GPGPUSample::GPGPUSample(Object* o)
	: Component(o, static_cast<std::string>(typeid(GPGPUSample).name()).substr(6))
{
	m_mesh = std::make_unique<Mesh>(PrimitiveType::BOARD);
	m_material = std::make_unique<Material>();

	Start();
}

GPGPUSample::~GPGPUSample() {

}

void GPGPUSample::Start() {
	m_material->SetActive();
	//Œã‚ÅUniform‚ðƒZƒbƒg‚·‚é

	Graphics::DrawInstancedWithMesh(m_mesh.get(), 1000);
}

void GPGPUSample::Update() {

}

void GPGPUSample::ProcessInput(const Uint8* state)const {

}