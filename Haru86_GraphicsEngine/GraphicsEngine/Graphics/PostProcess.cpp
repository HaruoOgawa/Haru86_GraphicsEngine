#include "PostProcess.h"
#include <iostream>
#include "GraphicsEngine/Graphics/Texture.h"
#include <GL/glew.h>

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
	m_BloomIntensity(0.0)
{
	printf("Create PostProcess Instance\n");
}

PostProcess::~PostProcess() {

}

void PostProcess::EnablePostProcess() {
	m_UsePostProcess = true;
}

const bool PostProcess::GetUsePostProcess()const {
	return m_UsePostProcess;
}

void PostProcess::DrawPolygonPostProcess(const std::shared_ptr<Texture> SrcTexture, const unsigned int& DestBuffer)const {
	printf("DrawPolygonPostProcess\n");
}

void PostProcess::DrawLatePostProcess(const std::shared_ptr<Texture> SrcTexture, const unsigned int& DestBuffer)const {
	printf("DrawLatePostProcess\n");
}

void PostProcess::EnableBloom(float bloomIntensity) {
	m_UseBloom = true;
	m_BloomIntensity = bloomIntensity;
}