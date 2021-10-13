#include "MeshRendererComponent.h"

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

}