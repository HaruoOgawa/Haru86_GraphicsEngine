#include "CBoxCollider.h"
#include "GraphicsEngine/Component/TransformComponent.h"

namespace physics {
	CBoxCollider::CBoxCollider(EObjectType ObjectType, std::shared_ptr<TransformComponent> Transform,
		glm::vec3 CenterPos, std::vector<glm::vec3> LocalAxis, glm::vec3 LocalAxisSize) 
		: ACollider(ObjectType, Transform),
		m_CenterPos(CenterPos),
		m_LocalAxis(LocalAxis),
		m_LocalAxisSize(LocalAxisSize)
	{
	}

	CBoxCollider::~CBoxCollider() {

	}

	bool CBoxCollider::DetectCollider() {
		return true;
	}

}