#include "RaymarchingObject.h"
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Game/Game.h"

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

	m_mesh->Draw();
}