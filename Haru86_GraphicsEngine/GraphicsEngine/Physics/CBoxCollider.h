#pragma once
#include "ACollider.h"

namespace physics {
	class CBoxCollider :
		public ACollider
	{
		CBoxCollider();
		virtual ~CBoxCollider();

		virtual bool DetectCollider() override;
	};
}


