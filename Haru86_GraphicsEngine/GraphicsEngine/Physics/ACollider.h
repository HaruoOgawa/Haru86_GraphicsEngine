#pragma once
#include "./ICollider.h"
#include "EObjectType.h"

namespace physics {
	class ACollider
	{
		EObjectType m_ObjectType;
	public:
		ACollider();
		virtual ~ACollider();

		virtual bool DetectCollider() = 0;

	private:

	};
}
