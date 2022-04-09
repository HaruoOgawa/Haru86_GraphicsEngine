#include "ACollider.h"

namespace physics {
	ACollider::ACollider() :
		m_ObjectType(EObjectType::STATIC)
	{

	}

	ACollider::~ACollider() {

	}

	bool ACollider::DetectCollider() {
		return true;
	}
}
