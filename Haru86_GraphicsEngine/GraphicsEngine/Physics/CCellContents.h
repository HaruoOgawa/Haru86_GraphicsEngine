#pragma once
#include <memory>

namespace physics {
	class CColliderCell;
	class ACollider;
	
	class CCellContents
	{
		std::shared_ptr<ACollider> m_Collider;
	public:
		CCellContents(const std::shared_ptr<ACollider>& Collider);
		virtual ~CCellContents();
	};
}