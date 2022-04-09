#include "CBoxCollider.h"

namespace physics {
	CBoxCollider::CBoxCollider() : ACollider()

	{

	}

	CBoxCollider::~CBoxCollider() {

	}

	bool CBoxCollider::DetectCollider() {
		return true;
	}

}