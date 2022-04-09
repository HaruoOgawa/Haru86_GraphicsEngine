#include "CSphereCollider.h"

namespace physics {
	CSphereCollider::CSphereCollider() : ACollider()
		
	{

	}
	
	CSphereCollider::~CSphereCollider() {

	}

	bool CSphereCollider::DetectCollider() {
		return true;
	}

}