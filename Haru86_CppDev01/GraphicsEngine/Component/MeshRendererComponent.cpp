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
	material = new Material();
}

MeshRendererComponent::MeshRendererComponent(class Object* o, std::string objPath)
	: Component(o, static_cast<std::string>(typeid(MeshRendererComponent).name()).substr(6)), myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = glTFLoader::Load(objPath);
	material = new Material();
}

MeshRendererComponent::MeshRendererComponent(Object* o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName)
	: Component(o, static_cast<std::string>(typeid(MeshRendererComponent).name()).substr(6)),myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = std::make_unique<Mesh>((primType));
	material = new Material(vertexShaderName,fragmentShaderName);
}

MeshRendererComponent::MeshRendererComponent(Object* o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName, std::string textureString)
	: Component(o, static_cast<std::string>(typeid(MeshRendererComponent).name()).substr(6)),myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = std::make_unique<Mesh>((primType));
	material = new Material(vertexShaderName,fragmentShaderName);
	if (GameRenderer::GetInstance()->font!=nullptr) {
		primTex = GameRenderer::GetInstance()->font->GetFontTexture(textureString,glm::vec3(1.0,1.0,1.0), 30);
	}
	/*primTex =new Texture();
	if (!primTex->Load("C:/Users/Haruo Ogawa/Pictures/noise.png")) {
		delete primTex;
		primTex = nullptr;
		printf("Cannot LoadTex");
	}
	else {
		printf("Tex is Loaded !!");
		printf("primTex: %p \n",primTex);
	}*/
	
}


MeshRendererComponent::MeshRendererComponent(class Object* o, std::string modelDataPath, std::string vertexShaderName, std::string fragmentShaderName)
	: Component(o, static_cast<std::string>(typeid(MeshRendererComponent).name()).substr(6)),myowner(o), primTex(nullptr)
{
	useZTest = true;
	mesh = glTFLoader::Load(modelDataPath);
	material = new Material(vertexShaderName,fragmentShaderName);
}



MeshRendererComponent::~MeshRendererComponent() {
	delete material;
	if (primTex != nullptr) {
		delete primTex;
	}
}

void MeshRendererComponent::Update() {

}

void MeshRendererComponent::Draw() {
	//ここでTextureをアクティブにする
	material->SetActiveTextureList();

	if (primTex != nullptr) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		primTex->SetActive();
		material->SetTexUniform("_fontTexture", primTex->GetTextureID());
	}

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

	for (auto clip : animationClips) {
		clip->callback(clip->lifeTimeRate);
	}

	mesh->Draw();
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

	for (auto clip : animationClips) {
		clip->callback(clip->lifeTimeRate);
	}

	mesh->Draw();
}



void MeshRendererComponent::ProcessInput(const Uint8* state)const {

}