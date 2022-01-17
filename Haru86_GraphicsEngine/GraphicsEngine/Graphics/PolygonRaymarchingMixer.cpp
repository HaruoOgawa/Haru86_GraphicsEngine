#include "PolygonRaymarchingMixer.h"
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Graphics/GameRenderer.h"
#include "GraphicsEngine/Graphics/Texture.h"

PolygonRaymarchingMixer::PolygonRaymarchingMixer() {
	m_material = std::make_unique<Material>("./Assets/Shader/PolygonRaymarchingMixer.vert", "./Assets/Shader/PolygonRaymarchingMixer.frag");
	m_mesh = std::make_unique<Mesh>(PrimitiveType::BOARD);
}

PolygonRaymarchingMixer::~PolygonRaymarchingMixer() {

}

void PolygonRaymarchingMixer::Draw() {
	m_material->SetActive();
	m_material->SetFloatUniform("_frameResolusion", GameRenderer::GetInstance()->frameResolusion);
	//polygon_frameTexture
	if (GameRenderer::GetInstance()->polygon_frameTexture != nullptr) {
		GameRenderer::GetInstance()->polygon_frameTexture->SetActive();
		m_material->SetTexUniform("polygon_frameTexture", GameRenderer::GetInstance()->polygon_frameTexture->GetTextureID());
		GameRenderer::GetInstance()->polygon_frameTexture->SetEactive();
	}
	//polygon_depthTexture
	if (GameRenderer::GetInstance()->polygon_depthTexture != nullptr) {
		GameRenderer::GetInstance()->polygon_depthTexture->SetActive();
		m_material->SetTexUniform("polygon_depthTexture", GameRenderer::GetInstance()->polygon_depthTexture->GetTextureID());
		GameRenderer::GetInstance()->polygon_depthTexture->SetEactive();
	}
	//raymarching_frameTexture
	if (GameRenderer::GetInstance()->raymarching_frameTexture != nullptr) {
		GameRenderer::GetInstance()->raymarching_frameTexture->SetActive();
		m_material->SetTexUniform("raymarching_frameTexture", GameRenderer::GetInstance()->raymarching_frameTexture->GetTextureID());
		GameRenderer::GetInstance()->raymarching_frameTexture->SetEactive();
	}
	//raymarching_depthTexture
	if (GameRenderer::GetInstance()->raymarching_depthTexture != nullptr) {
		GameRenderer::GetInstance()->raymarching_depthTexture->SetActive();
		m_material->SetTexUniform("raymarching_depthTexture", GameRenderer::GetInstance()->raymarching_depthTexture->GetTextureID());
		GameRenderer::GetInstance()->raymarching_depthTexture->SetEactive();
	}
	m_mesh->Draw();
}