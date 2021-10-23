#include "GameObject.h"
#include "./Game.h"
#include "./TransformComponent.h"
#include "./MeshRendererComponent.h"

GameObject::GameObject(PrimitiveType primType) 
	: Object(), renderOrder(RenderQueue::Geometry)
{
	Game::GetInstance()->gameObjectList.emplace_back(this);
	meshComp = new MeshRendererComponent(this, primType);
	Object::AddComponent(meshComp);
}

GameObject::GameObject(PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName)
	: Object(), renderOrder(RenderQueue::Geometry)
{
	Game::GetInstance()->gameObjectList.emplace_back(this);
	meshComp = new MeshRendererComponent(this, primType,vertexShaderName,fragmentShaderName);
	Object::AddComponent(meshComp);
}

GameObject::~GameObject() {
	
}

void GameObject::UseZTest(bool use) {
	meshComp->useZTest = use; 
}

void GameObject::SetRenderOlder(int order) {
	renderOrder = order;
}

void GameObject::ProcessInput(const Uint8* state) {
	//printf("------------------------------------------------------------------------ \n");
	for (auto comp : myComponent) {
		comp.second->ProcessInput(state);
		//printf("comp.first: %s \n",comp.first.c_str());

	}
	//printf("myComponent.size(): %d \n", myComponent.size());
}