#pragma once
#include "ACollider.h"

namespace physics {
	class CSphereCollider :
		public ACollider
	{
	public:
		CSphereCollider();
		virtual ~CSphereCollider();

		virtual bool DetectCollider() override;
	};
}