#include "MeshRendererComponent.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "./TransformComponent.h"
#include <string>
#include <iostream>
#include "../Graphics/GraphicsRenderer.h"
#include "./TimelineComponent.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Font.h"
#include "GraphicsEngine/Graphics/glTFLoader.h"
#include "GraphicsEngine/Graphics/glTFLoader.h"

MeshRendererComponent::MeshRendererComponent(Object* o, PrimitiveType primType)
	: Component(o), myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = std::make_unique<Mesh>((primType));
	mesh->glDrawType = GLDrawType::NONE;
	material = std::make_shared<Material>();
}

MeshRendererComponent::MeshRendererComponent(Object* o, PrimitiveType primType, std::map<GLenum, std::string> shaders)
	: Component(o), myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = std::make_unique<Mesh>((primType));
	if (shaders.find(GL_TESS_CONTROL_SHADER)!=shaders.end()) {
		mesh->glDrawType = GLDrawType::TESSELLATION;
	}
	else {
		mesh->glDrawType = GLDrawType::NONE;
	}
	material = std::make_shared<Material>(shaders);
}

MeshRendererComponent::MeshRendererComponent(Object* o, std::string objPath)
	: Component(o), myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = glTFLoader::Load(objPath);
	mesh->glDrawType = GLDrawType::NONE;
	material = std::make_shared<Material>();
}

MeshRendererComponent::MeshRendererComponent(Object* o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName)
	: Component(o),myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = std::make_unique<Mesh>((primType));
	mesh->glDrawType = GLDrawType::NONE;
	material = std::make_shared<Material>(vertexShaderName,fragmentShaderName);
}

MeshRendererComponent::MeshRendererComponent(Object* o, PrimitiveType primType, std::string vertexShaderName, std::string tessellationShaderName[2], std::string fragmentShaderName)
	: Component(o),myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = std::make_unique<Mesh>((primType));
	mesh->glDrawType = GLDrawType::TESSELLATION;
	material = std::make_shared<Material>(vertexShaderName,tessellationShaderName,fragmentShaderName);
}

MeshRendererComponent::MeshRendererComponent(Object* o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName, std::string textureString)
	: Component(o),myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = std::make_unique<Mesh>((primType));
	mesh->glDrawType = GLDrawType::NONE;
	material = std::make_shared<Material>(vertexShaderName,fragmentShaderName);
	if (GraphicsRenderer::GetInstance()->font!=nullptr) {
		primTex = GraphicsRenderer::GetInstance()->font->GetFontTexture(textureString,glm::vec3(1.0,1.0,1.0), 30);
	}
	
}


MeshRendererComponent::MeshRendererComponent(Object* o, std::string modelDataPath, std::string vertexShaderName, std::string fragmentShaderName)
	: Component(o),myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = glTFLoader::Load(modelDataPath);
	mesh->glDrawType = GLDrawType::NONE;
	material = std::make_shared<Material>(vertexShaderName,fragmentShaderName);
}

MeshRendererComponent::~MeshRendererComponent() {

}

void MeshRendererComponent::Update() {

}

void MeshRendererComponent::Draw() {
	
	if (useZTest == true) {
		glEnable(GL_DEPTH_TEST);
	}
	else if(useZTest==false){
		glDisable(GL_DEPTH_TEST);
	}
	
	material->SetActive();
	material->SetMatrixUniform("MVPMatrix", owner->transform->GetMVPMatrix());
	material->SetMatrixUniform("MMatrix", owner->transform->GetMMatrix());
	material->SetMatrixUniform("VMatrix", owner->transform->GetVMatrix());
	material->SetMatrixUniform("PMatrix", owner->transform->GetPMatrix());
	material->SetFloatUniform("_time", game->time);
	material->SetFloatUniform("_deltaTime", game->deltaTime);
	material->SetVec2Uniform("_resolution", GraphicsRenderer::GetInstance()->GetScreenSize());

	if (primTex != nullptr) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		primTex->SetActive();
		material->SetTexUniform("_fontTexture", primTex->GetTextureID());
	}

	//ここでTextureをアクティブにする
	material->SetActiveTextureList();

	for (auto clip : animationClips) {
		clip->callback(clip->lifeTimeRate);
	}

	if (mesh->glDrawType == GLDrawType::TESSELLATION) {
		//glPatchParameteri(GL_PATCH_VERTICES, 4);
		mesh->Draw(mesh->glDrawType);
	}
	else {
		mesh->Draw();
	}

	//使い終わったらここでTextureを非アクティブにする
	material->SetEactiveTextureList();
}

void MeshRendererComponent::DrawBoard() {
	if (useZTest == true) {
		glEnable(GL_DEPTH_TEST);
	}
	else if(useZTest==false){
		glDisable(GL_DEPTH_TEST);
	}
	
	material->SetActive();
	material->SetMatrixUniform("MVPMatrix", owner->transform->GetMVPMatrix());
	material->SetMatrixUniform("MMatrix", owner->transform->GetMMatrix());
	material->SetMatrixUniform("VMatrix", owner->transform->GetVMatrix());
	material->SetMatrixUniform("PMatrix", owner->transform->GetPMatrix());
	material->SetFloatUniform("_time", game->time);
	material->SetFloatUniform("_deltaTime", game->deltaTime);
	material->SetVec2Uniform("_resolution", GraphicsRenderer::GetInstance()->GetScreenSize());
	material->SetFloatUniform("_frameResolusion", GraphicsRenderer::GetInstance()->frameResolusion);
	
	// PolygonPostProcessのテスト
	/*if (GraphicsRenderer::GetInstance()->m_PolygonPostProcess_FrameTexture != nullptr) {
		GraphicsRenderer::GetInstance()->m_PolygonPostProcess_FrameTexture->SetActive();
		material->SetTexUniform("frameTex", GraphicsRenderer::GetInstance()->m_PolygonPostProcess_FrameTexture->GetTextureID());
		GraphicsRenderer::GetInstance()->m_PolygonPostProcess_FrameTexture->SetEactive();
	}*/

	// PostProcess後の最終結果 → m_LatePostProcess_FrameTexture
	if (GraphicsRenderer::GetInstance()->m_LatePostProcess_FrameTexture != nullptr) {
		GraphicsRenderer::GetInstance()->m_LatePostProcess_FrameTexture->SetActive();
		material->SetTexUniform("frameTex", GraphicsRenderer::GetInstance()->m_LatePostProcess_FrameTexture->GetTextureID());
		GraphicsRenderer::GetInstance()->m_LatePostProcess_FrameTexture->SetEactive();
	}

	for (auto clip : animationClips) {
		clip->callback(clip->lifeTimeRate);
	}

	mesh->Draw();
}



void MeshRendererComponent::ProcessInput(const Uint8* state) {

}