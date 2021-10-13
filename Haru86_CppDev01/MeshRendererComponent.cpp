#include "MeshRendererComponent.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

MeshRendererComponent::MeshRendererComponent(Object* o, std::string vertexShaderName, std::string fragmentShaderName)
	: Component(o)
{
	mesh =new VertexArray();
	material = new Material(vertexShaderName,fragmentShaderName);
}

MeshRendererComponent::~MeshRendererComponent() {
	delete mesh;
	delete material;
}

void MeshRendererComponent::Update() {

}

void MeshRendererComponent::Draw() {
	material->SetActive();
	//material->SetMatrixUniform("MVPMat",)
	mesh->SetActive();
	glDrawElements(GL_TRIANGLES, mesh->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}