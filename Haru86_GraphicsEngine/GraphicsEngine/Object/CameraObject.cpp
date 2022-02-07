#include "CameraObject.h"
#include "GraphicsEngine/Component/CameraComponent.h"
#include "GraphicsEngine/Game/Game.h"

CameraObject::CameraObject(CameraType cameraType)
	: Object(),m_cameraType(cameraType)
{
	m_cameraComponent =  std::make_shared<CameraComponent>(this,cameraType);
	AddComponent<CameraComponent>(m_cameraComponent);
}

CameraObject::~CameraObject() {
}

void CameraObject::Update() {

}