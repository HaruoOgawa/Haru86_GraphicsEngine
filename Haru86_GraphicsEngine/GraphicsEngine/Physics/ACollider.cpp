#include "ACollider.h"

namespace physics {
	ACollider::ACollider(EObjectType ObjectType, TransformComponent* Transform) :
		m_ObjectType(ObjectType),
		m_Transform(Transform)
	{
	}

	ACollider::~ACollider() {

	}

	bool ACollider::DetectCollider() {
		return true;
	}
}
