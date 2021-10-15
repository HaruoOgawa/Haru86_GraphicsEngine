#include "GameObject.h"

#include "./TransformComponent.h"
#include "./MeshRendererComponent.h"

GameObject::GameObject(Game* g, PrimitiveType primType) 
	: Object(g)
{
	meshComp = new MeshRendererComponent(g,this, primType);
	Object::AddComponent(meshComp);
}

GameObject::GameObject(Game* g, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName)
	: Object(g)
{
	meshComp = new MeshRendererComponent(g,this, primType,vertexShaderName,fragmentShaderName);
	Object::AddComponent(meshComp);
}

GameObject::~GameObject() {
	
}


