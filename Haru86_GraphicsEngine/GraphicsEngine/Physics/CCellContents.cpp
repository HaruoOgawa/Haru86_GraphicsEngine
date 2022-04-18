#include "CCellContents.h"
#include "ACollider.h"
#include "CColliderCell.h"

namespace physics {
	CCellContents::CCellContents(const std::shared_ptr<ACollider>& Collider) :
		m_Collider(Collider)
	{
	}

	CCellContents::~CCellContents() {

	}
}