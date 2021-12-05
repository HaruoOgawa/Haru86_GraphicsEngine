#include "CameraObject.h"
#include "GraphicsEngine/Component/CameraComponent.h"

CameraObject::CameraObject(CameraType cameraType)
	: Object()
{
	m_cameraComponent = new CameraComponent(this);
	AddComponent(m_cameraComponent);
}

CameraObject::~CameraObject() {

}

void CameraObject::Update() {

}