#include "GameObject.h"

#include "./TransformComponent.h"
#include "./MeshRendererComponent.h"

GameObject::GameObject(Game* g, std::string vertexShaderName, std::string fragmentShaderName)
	: Object(g)
{
	meshComp = new MeshRendererComponent(this,vertexShaderName,fragmentShaderName);
	Object::AddComponent(meshComp);
}

GameObject::~GameObject() {
	
}


