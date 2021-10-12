#include "GameObject.h"

#include "./TransformComponent.h"
#include "./MeshRendererComponent.h"

GameObject::GameObject(Game* g)
	: Object(g)
{
	MeshRendererComponent* meshComp = new MeshRendererComponent(this);
	Object::AddComponent(meshComp);
}

GameObject::~GameObject() {
	
}


