#include "GameObject.h"
#include "./Game.h"
#include "./TransformComponent.h"
#include "./MeshRendererComponent.h"

GameObject::GameObject(Game* g, PrimitiveType primType) 
	: Object(g)
{
	g->gameObjectList.emplace_back(this);
	meshComp = new MeshRendererComponent(g,this, primType);
	Object::AddComponent(meshComp);
}

GameObject::GameObject(Game* g, PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName)
	: Object(g)
{
	g->gameObjectList.emplace_back(this);
	meshComp = new MeshRendererComponent(g,this, primType,vertexShaderName,fragmentShaderName);
	Object::AddComponent(meshComp);
}

GameObject::~GameObject() {
	
}


