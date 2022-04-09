#include "CSphereCollider.h"

namespace physics {
	CSphereCollider::CSphereCollider(EObjectType ObjectType, std::shared_ptr<TransformComponent> Transform, glm::vec3 CenterPos, float Radius) 
		: ACollider(ObjectType, Transform),
		m_CenterPos(CenterPos),
		m_Radius(Radius)
	{
	}
	
	CSphereCollider::~CSphereCollider() {

	}

	bool CSphereCollider::DetectCollider() {
		return true;
	}

}