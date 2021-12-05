#include "CameraComponent.h"
#include "GraphicsEngine/Object/CameraObject.h"

CameraComponent::CameraComponent(Object* o, enum class CameraType cameraType)
	: Component(o, static_cast<std::string>(typeid(CameraComponent).name()).substr(6))
	, m_cameraType(cameraType)
{

}

CameraComponent::~CameraComponent() {

}

void CameraComponent::Start() {

}

void CameraComponent::Update() {

}

void CameraComponent::ProcessInput(const Uint8* state)const {

}