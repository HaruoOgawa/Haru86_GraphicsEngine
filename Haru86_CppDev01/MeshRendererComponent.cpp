#include "MeshRendererComponent.h"

MeshRendererComponent::MeshRendererComponent(Object* o)
	: Component(o)
{
	mesh =new VertexArray();
	material = new Material();
}

MeshRendererComponent::~MeshRendererComponent() {

}

void MeshRendererComponent::Update() {

}

void MeshRendererComponent::Draw() {

}