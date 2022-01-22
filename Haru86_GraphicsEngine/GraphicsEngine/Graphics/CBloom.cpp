#include "CBloom.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"
#include "GraphicsEngine/Game/Game.h"
#include "GraphicsEngine/Graphics/GameRenderer.h"

CBloom::CBloom():
	m_IlluminanceMap(std::make_shared<Texture>()),
	m_BlurMap(std::make_shared<Texture>()),
	m_IlluminanceBuffer(0),
	m_BlurBuffer(0)
{
	Initialize();
}

CBloom::~CBloom() {

}

void CBloom::Release() {

}

void CBloom::Initialize() {
	m_IlluminanceMaterial = std::make_shared<Material>("./Assets/Shader/StandardRenderBoard.vert", "./Assets/Shader/BloomIlluminance.frag");
	m_BlurMaterial = std::make_shared<Material>("./Assets/Shader/StandardRenderBoard.vert", "./Assets/Shader/BloomBlur.frag");
	m_BloomResultMaterial = std::make_shared<Material>("./Assets/Shader/StandardRenderBoard.vert", "./Assets/Shader/BloomResult.frag");
	m_mesh = std::make_shared<Mesh>(PrimitiveType::BOARD);

	// Create FrameBuffer  Œã‚Ù‚ÇHDRTexture‚É‚·‚é
	if(!GameRenderer::GetInstance()->CreateFrameBuffer(m_IlluminanceMap, m_IlluminanceBuffer,GL_RGBA, GL_RGBA))printf("Cannot Create FrameBuffer\n");
	if(!GameRenderer::GetInstance()->CreateFrameBuffer(m_BlurMap, m_BlurBuffer,GL_RGBA, GL_RGBA))printf("Cannot Create FrameBuffer\n");
}

void CBloom::Draw(const std::shared_ptr<Texture> SrcTexture, const unsigned int& DestBuffer) {
	// Illuminance
	Game::GetInstance()->renderingTarget = ERerderingTarget::COLOR;
	glBindFramebuffer(GL_FRAMEBUFFER, m_IlluminanceBuffer);
	glViewport(0, 0, static_cast<int>(GameRenderer::GetInstance()->GetScreenSize().x * GameRenderer::GetInstance()->frameResolusion), static_cast<int>(GameRenderer::GetInstance()->GetScreenSize().y * GameRenderer::GetInstance()->frameResolusion));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	m_IlluminanceMaterial->SetActive();
	m_IlluminanceMaterial->SetFloatUniform("_time", Game::GetInstance()->time);
	m_IlluminanceMaterial->SetVec2Uniform("_resolution", GameRenderer::GetInstance()->GetScreenSize());
	m_IlluminanceMaterial->SetFloatUniform("_frameResolusion", GameRenderer::GetInstance()->frameResolusion);
	m_IlluminanceMaterial->SetTexUniform("_SrcTexture", SrcTexture->GetTextureID());
	m_mesh->Draw();

	// Blur
	Game::GetInstance()->renderingTarget = ERerderingTarget::COLOR;
	glBindFramebuffer(GL_FRAMEBUFFER, m_BlurBuffer);
	glViewport(0, 0, static_cast<int>(GameRenderer::GetInstance()->GetScreenSize().x * GameRenderer::GetInstance()->frameResolusion), static_cast<int>(GameRenderer::GetInstance()->GetScreenSize().y * GameRenderer::GetInstance()->frameResolusion));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	m_BlurMaterial->SetActive();
	m_BlurMaterial->SetFloatUniform("_time", Game::GetInstance()->time);
	m_BlurMaterial->SetVec2Uniform("_resolution", GameRenderer::GetInstance()->GetScreenSize());
	m_BlurMaterial->SetFloatUniform("_frameResolusion", GameRenderer::GetInstance()->frameResolusion);
	if (m_IlluminanceMap) {
		m_IlluminanceMap->SetActive();
		m_BlurMaterial->SetTexUniform("_IlluminanceTexture", m_IlluminanceMap->GetTextureID());
		m_IlluminanceMap->SetEactive();
	}
	m_mesh->Draw();

	// Result
	Game::GetInstance()->renderingTarget = ERerderingTarget::COLOR;
	glBindFramebuffer(GL_FRAMEBUFFER, DestBuffer);
	glViewport(0, 0, static_cast<int>(GameRenderer::GetInstance()->GetScreenSize().x * GameRenderer::GetInstance()->frameResolusion), static_cast<int>(GameRenderer::GetInstance()->GetScreenSize().y * GameRenderer::GetInstance()->frameResolusion));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	m_BloomResultMaterial->SetActive();
	m_BloomResultMaterial->SetFloatUniform("_time", Game::GetInstance()->time);
	m_BloomResultMaterial->SetVec2Uniform("_resolution", GameRenderer::GetInstance()->GetScreenSize());
	m_BloomResultMaterial->SetFloatUniform("_frameResolusion", GameRenderer::GetInstance()->frameResolusion);
	if (m_BlurMap) {
		m_BlurMap->SetActive();
		m_BloomResultMaterial->SetTexUniform("_BlurTexture", m_BlurMap->GetTextureID());
		m_BlurMap->SetEactive();
	}
	m_mesh->Draw();

}