#include "../Object/GameObject.h"
#include "../Game/Game.h"
#include "../Component/TransformComponent.h"
#include "../Component/MeshRendererComponent.h"


GameObject::GameObject(PrimitiveType primType) 
	: Object(), renderOrder(RenderQueue::Geometry), renderType(RenderType::DefaultBuffer), animTime(0.0f)
{
	Game::GetInstance()->gameObjectList.emplace_back(this);
	meshComp =  std::make_shared<MeshRendererComponent>(this, primType);
	AddComponent<MeshRendererComponent>(meshComp);
}

GameObject::GameObject(PrimitiveType primType, std::map<GLenum, std::string> shaders)
	: Object(), renderOrder(RenderQueue::Geometry), renderType(RenderType::DefaultBuffer), animTime(0.0f)
{
	Game::GetInstance()->gameObjectList.emplace_back(this);
	meshComp = std::make_shared<MeshRendererComponent>(this, primType,shaders);
	AddComponent<MeshRendererComponent>(meshComp);
}


GameObject::GameObject(std::string objPath)
	: Object(), renderOrder(RenderQueue::Geometry), renderType(RenderType::DefaultBuffer), animTime(0.0f)
{
	Game::GetInstance()->gameObjectList.emplace_back(this);
	meshComp = std::make_shared<MeshRendererComponent>(this, objPath);
	AddComponent<MeshRendererComponent>(meshComp);
}

GameObject::GameObject(PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName)
	: Object(), renderOrder(RenderQueue::Geometry), renderType(RenderType::DefaultBuffer), animTime(0.0f)
{
	Game::GetInstance()->gameObjectList.emplace_back(this);
	meshComp = std::make_shared<MeshRendererComponent>(this, primType,vertexShaderName,fragmentShaderName);
	AddComponent<MeshRendererComponent>(meshComp);
}

GameObject::GameObject(PrimitiveType primType, std::string vertexShaderName, std::string tessellationShaderName[2], std::string fragmentShaderName)
	: Object(), renderOrder(RenderQueue::Geometry), renderType(RenderType::DefaultBuffer), animTime(0.0f)
{
	Game::GetInstance()->gameObjectList.emplace_back(this);
	meshComp = std::make_shared<MeshRendererComponent>(this, primType,vertexShaderName,tessellationShaderName,fragmentShaderName);
	AddComponent<MeshRendererComponent>(meshComp);
}

GameObject::GameObject(PrimitiveType primType, std::string vertexShaderName, std::string fragmentShaderName, std::string textureString)
	: Object(), renderOrder(RenderQueue::UI), renderType(RenderType::DefaultBuffer), animTime(0.0f)
{
	Game::GetInstance()->gameObjectList.emplace_back(this);
	meshComp = std::make_shared<MeshRendererComponent>(this, primType,vertexShaderName,fragmentShaderName, textureString);
	AddComponent<MeshRendererComponent>(meshComp);
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
	
	meshComp = std::make_shared<MeshRendererComponent>(this, primType, vertexShaderName, fragmentShaderName);
	AddComponent<MeshRendererComponent>(meshComp);
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