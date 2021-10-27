#include "MeshRendererComponent.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "./TransformComponent.h"
#include <string>
#include <iostream>
#include "./GameRenderer.h"
#include "./TimelineComponent.h"

MeshRendererComponent::MeshRendererComponent(Object* o, PrimitiveType primType)
	: Component(o, static_cast<std::string>(typeid(MeshRendererComponent).name()).substr(6)), myowner(o)
{
	useZTest = true;
	mesh = new VertexArray(primType);
	material = new Material();
}

MeshRendererComponent::MeshRendererComponent(Object* o, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName)
	: Component(o, static_cast<std::string>(typeid(MeshRendererComponent).name()).substr(6)),myowner(o)
{
	useZTest = true;
	mesh =new VertexArray(primType);
	material = new Material(vertexShaderName,fragmentShaderName);
}



MeshRendererComponent::~MeshRendererComponent() {
	delete mesh;
	delete material;
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

	printf("Call MeshRenderer CallbackS !! \n");
	for (auto clip : animationClips) {
		clip->callback();
	}

	mesh->SetActive();
	glDrawElements(GL_TRIANGLES, mesh->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
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

	mesh->SetActive();
	glDrawElements(GL_TRIANGLES, mesh->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}



void MeshRendererComponent::ProcessInput(const Uint8* state)const {

}