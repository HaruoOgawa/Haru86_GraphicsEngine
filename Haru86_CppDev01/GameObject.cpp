#include "GameObject.h"
#include "./Game.h"
#include "./TransformComponent.h"
#include "./MeshRendererComponent.h"

GameObject::GameObject(PrimitiveType primType) 
	: Object(), renderOrder(RenderQueue::Geometry), renderType(RenderType::DefaultBuffer), animTime(0.0f)
{
	Game::GetInstance()->gameObjectList.emplace_back(this);
	meshComp = new MeshRendererComponent(this, primType);
	Object::AddComponent(meshComp);
}

GameObject::GameObject(PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName)
	: Object(), renderOrder(RenderQueue::Geometry), renderType(RenderType::DefaultBuffer), animTime(0.0f)
{
	Game::GetInstance()->gameObjectList.emplace_back(this);
	meshComp = new MeshRendererComponent(this, primType,vertexShaderName,fragmentShaderName);
	Object::AddComponent(meshComp);
}

GameObject::GameObject(PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName, std::string textureString)
	: Object(), renderOrder(RenderQueue::UI), renderType(RenderType::DefaultBuffer), animTime(0.0f)
{
	Game::GetInstance()->gameObjectList.emplace_back(this);
	meshComp = new MeshRendererComponent(this, primType,vertexShaderName,fragmentShaderName, textureString);
	Object::AddComponent(meshComp);
	UseZTest(false);
	SetRenderOlder(RenderQueue::UI);
}

GameObject::GameObject(PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName, RenderType rt)
	:Object(), renderOrder(RenderQueue::UI), renderType(rt), animTime(0.0f)
{
	if (renderType == RenderType::FrameBuffer) {
		Game::GetInstance()->boardGameObjectList.emplace_back(this);
	}
	else if (renderType==RenderType::PostProcess) {
		Game::GetInstance()->postProcessGameObjectList.emplace_back(this);
	}
	
	meshComp = new MeshRendererComponent(this, primType, vertexShaderName, fragmentShaderName);
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
	for (auto comp : myComponent) {
		comp.second->ProcessInput(state);
	}
}