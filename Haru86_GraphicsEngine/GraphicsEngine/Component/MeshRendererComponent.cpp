#include "MeshRendererComponent.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "./TransformComponent.h"
#include <string>
#include <iostream>
#include "../Graphics/GameRenderer.h"
#include "./TimelineComponent.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Font.h"
#include "GraphicsEngine/Graphics/glTFLoader.h"
#include "GraphicsEngine/Graphics/glTFLoader.h"

MeshRendererComponent::MeshRendererComponent(Object* o, PrimitiveType primType)
	: Component(o, static_cast<std::string>(typeid(MeshRendererComponent).name()).substr(6)), myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = std::make_unique<Mesh>((primType));
	mesh->glDrawType = GLDrawType::NONE;
	material = std::make_shared<Material>();
}

MeshRendererComponent::MeshRendererComponent(Object* o, PrimitiveType primType, std::map<GLenum, std::string> shaders)
	: Component(o, static_cast<std::string>(typeid(MeshRendererComponent).name()).substr(6)), myowner(o), primTex(nullptr)
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
	: Component(o, static_cast<std::string>(typeid(MeshRendererComponent).name()).substr(6)), myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = glTFLoader::Load(objPath);
	mesh->glDrawType = GLDrawType::NONE;
	material = std::make_shared<Material>();
}

MeshRendererComponent::MeshRendererComponent(Object* o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName)
	: Component(o, static_cast<std::string>(typeid(MeshRendererComponent).name()).substr(6)),myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = std::make_unique<Mesh>((primType));
	mesh->glDrawType = GLDrawType::NONE;
	material = std::make_shared<Material>(vertexShaderName,fragmentShaderName);
}

MeshRendererComponent::MeshRendererComponent(Object* o, PrimitiveType primType, std::string vertexShaderName, std::string tessellationShaderName[2], std::string fragmentShaderName)
	: Component(o, static_cast<std::string>(typeid(MeshRendererComponent).name()).substr(6)),myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = std::make_unique<Mesh>((primType));
	mesh->glDrawType = GLDrawType::TESSELLATION;
	material = std::make_shared<Material>(vertexShaderName,tessellationShaderName,fragmentShaderName);
}

MeshRendererComponent::MeshRendererComponent(Object* o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName, std::string textureString)
	: Component(o, static_cast<std::string>(typeid(MeshRendererComponent).name()).substr(6)),myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = std::make_unique<Mesh>((primType));
	mesh->glDrawType = GLDrawType::NONE;
	material = std::make_shared<Material>(vertexShaderName,fragmentShaderName);
	if (GameRenderer::GetInstance()->font!=nullptr) {
		primTex = GameRenderer::GetInstance()->font->GetFontTexture(textureString,glm::vec3(1.0,1.0,1.0), 30);
	}
	
}


MeshRendererComponent::MeshRendererComponent(Object* o, std::string modelDataPath, std::string vertexShaderName, std::string fragmentShaderName)
	: Component(o, static_cast<std::string>(typeid(MeshRendererComponent).name()).substr(6)),myowner(o), primTex(nullptr)
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
	material->SetVec2Uniform("_resolution", GameRenderer::GetInstance()->GetScreenSize());

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
	material->SetVec2Uniform("_resolution", GameRenderer::GetInstance()->GetScreenSize());
	material->SetFloatUniform("_frameResolusion", GameRenderer::GetInstance()->frameResolusion);
	
	if (GameRenderer::GetInstance()->polygon_frameTexture !=nullptr) {
		GameRenderer::GetInstance()->polygon_frameTexture->SetActive();
		material->SetTexUniform("frameTex", GameRenderer::GetInstance()->polygon_frameTexture->GetTextureID());
		GameRenderer::GetInstance()->polygon_frameTexture->SetEactive();
	}
	
	if (GameRenderer::GetInstance()->polygon_depthTexture !=nullptr) {
		GameRenderer::GetInstance()->polygon_depthTexture->SetActive();
		//material->SetTexUniform("frameTex", GameRenderer::GetInstance()->polygon_depthTexture->GetTextureID());
		GameRenderer::GetInstance()->polygon_depthTexture->SetEactive();
	}

	for (auto clip : animationClips) {
		clip->callback(clip->lifeTimeRate);
	}

	mesh->Draw();
}



void MeshRendererComponent::ProcessInput(const Uint8* state)const {

}