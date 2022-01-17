#include "PolygonRaymarchingMixer.h"
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/Graphics/Mesh.h"

PolygonRaymarchingMixer::PolygonRaymarchingMixer() {
	m_material = std::make_unique<Material>("./Assets/Shader/PolygonRaymarchingMixer.vert", "./Assets/Shader/PolygonRaymarchingMixer.frag");
	m_mesh = std::make_unique<Mesh>(PrimitiveType::BOARD);
}

PolygonRaymarchingMixer::~PolygonRaymarchingMixer() {

}

void PolygonRaymarchingMixer::Draw() {
	m_material->SetActive();

	m_mesh->Draw();
}