#include "MeshRendererComponent.h"

MeshRendererComponent::MeshRendererComponent(Object* o)
	: Component(o)
{
	mesh =new VertexArray();
	material = new Material();
}

MeshRendererComponent::~MeshRendererComponent() {
	delete mesh;
	delete material;
}

void MeshRendererComponent::Update() {

}

void MeshRendererComponent::Draw() {

}