#include "GameObject.h"
#include "./Game.h"
#include "./TransformComponent.h"
#include "./MeshRendererComponent.h"

GameObject::GameObject(PrimitiveType primType) 
	: Object()
{
	Game::GetInstance()->gameObjectList.emplace_back(this);
	meshComp = new MeshRendererComponent(Game::GetInstance(),this, primType);
	Object::AddComponent(meshComp);
}

GameObject::GameObject(PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName)
	: Object()
{
	Game::GetInstance()->gameObjectList.emplace_back(this);
	meshComp = new MeshRendererComponent(Game::GetInstance(),this, primType,vertexShaderName,fragmentShaderName);
	Object::AddComponent(meshComp);
}

GameObject::~GameObject() {
	
}


