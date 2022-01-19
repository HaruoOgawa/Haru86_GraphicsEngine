#include "PostProcess.h"
#include <iostream>
#include "GraphicsEngine/Graphics/Texture.h"
#include <GL/glew.h>
#include "CBloom.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/Graphics/GameRenderer.h"
#include "GraphicsEngine/Graphics/Mesh.h"
#include "GraphicsEngine/Graphics/Material.h"
#include "GraphicsEngine/Game/Game.h"

//instance‚ð’è‹`‚·‚é
PostProcess* PostProcess::instance = nullptr;

void PostProcess::CreateInstance() {
	if (!instance)instance = new PostProcess();
}

PostProcess* PostProcess::GetInstance() {
	if (instance) return instance;
}

void PostProcess::DestroyInstance() {
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

PostProcess::PostProcess():
	m_UsePostProcess(false),
	m_UseBloom(false),
	m_BloomIntensity(0.0),
	m_Bloom(std::make_unique<CBloom>()),
	m_BloomTexture(std::make_shared<Texture>())
{
	Initialize();
}

PostProcess::~PostProcess() {

}

void PostProcess::Initialize() {

	m_mesh = std::make_shared<Mesh>(PrimitiveType::BOARD);
	m_material = std::make_shared<Material>("./Assets/Shader/StandardRenderBoard.vert", "./Assets/Shader/PolygonPostProcess.frag");
	m_LateMaterial = std::make_shared<Material>("./Assets/Shader/StandardRenderBoard.vert", "./Assets/Shader/LatePostProcess.frag");

	if (!GameRenderer::GetInstance()->CreateFrameBuffer(m_BloomTexture, m_BloomFrameBuffer,GL_RGBA,GL_RGBA)) {
		printf("Cannot Create FrameBuffer\n");
	}
}

void PostProcess::Release() {

}

void PostProcess::EnablePostProcess() {
	m_UsePostProcess = true;
}

const bool PostProcess::GetUsePostProcess()const {
	return m_UsePostProcess;
}

void PostProcess::DrawPolygonPostProcess(const std::shared_ptr<Texture> SrcTexture, const unsigned int& DestBuffer)const {
	if (m_UsePostProcess) {
		// Draw Bloom
		if (m_UseBloom)m_Bloom->Draw(SrcTexture, m_BloomFrameBuffer);

		// Draw PostProcess Result
		Game::GetInstance()->renderingTarget = ERerderingTarget::COLOR;
		glBindFramebuffer(GL_FRAMEBUFFER, DestBuffer);
		glViewport(0, 0, static_cast<int>(GameRenderer::GetInstance()->GetScreenSize().x * GameRenderer::GetInstance()->frameResolusion), static_cast<int>(GameRenderer::GetInstance()->GetScreenSize().y * GameRenderer::GetInstance()->frameResolusion));

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		// draw PostProcess Board
		m_material->SetActive();

		// Bloom
		if (m_BloomTexture&& m_UseBloom) {
			m_BloomTexture->SetActive();
			m_material->SetTexUniform("_BloomTexture", m_BloomTexture->GetTextureID());
			m_material->SetFloatUniform("_UseBloom", 1.0);
			m_BloomTexture->SetEactive();
		}
		else {
			m_material->SetFloatUniform("_UseBloom", 0.0);
		}

		m_mesh->Draw();
	}
	else {
		// Draw PostProcess Result
		Game::GetInstance()->renderingTarget = ERerderingTarget::COLOR;
		glBindFramebuffer(GL_FRAMEBUFFER, DestBuffer);
		glViewport(0, 0, static_cast<int>(GameRenderer::GetInstance()->GetScreenSize().x * GameRenderer::GetInstance()->frameResolusion), static_cast<int>(GameRenderer::GetInstance()->GetScreenSize().y * GameRenderer::GetInstance()->frameResolusion));

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		// draw PostProcess Board
		m_material->SetActive();
		m_material->SetFloatUniform("_UseBloom", 0.0);
		m_mesh->Draw();

	}
}

void PostProcess::DrawLatePostProcess(const std::shared_ptr<Texture> SrcTexture, const unsigned int& DestBuffer)const {
	if (m_UsePostProcess) {
		
		// Draw PostProcess Result
		glBindFramebuffer(GL_FRAMEBUFFER, DestBuffer);
		glViewport(0, 0, static_cast<int>(GameRenderer::GetInstance()->GetScreenSize().x * GameRenderer::GetInstance()->frameResolusion), static_cast<int>(GameRenderer::GetInstance()->GetScreenSize().y * GameRenderer::GetInstance()->frameResolusion));

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		m_LateMaterial->SetActive();
		// Sample SrcTexture
		m_LateMaterial->SetTexUniform("_SrcTexture", SrcTexture->GetTextureID());
		m_mesh->Draw();
	}
	else {
		// Draw PostProcess Result
		glBindFramebuffer(GL_FRAMEBUFFER, DestBuffer);
		glViewport(0, 0, static_cast<int>(GameRenderer::GetInstance()->GetScreenSize().x * GameRenderer::GetInstance()->frameResolusion), static_cast<int>(GameRenderer::GetInstance()->GetScreenSize().y * GameRenderer::GetInstance()->frameResolusion));

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		m_LateMaterial->SetActive();

		m_mesh->Draw();
	}
}

void PostProcess::EnableBloom(float bloomIntensity) {
	m_UseBloom = true;
	m_BloomIntensity = bloomIntensity;
}

void PostProcess::DrawBloom() {

}