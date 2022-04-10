#pragma once
#include "ACollider.h"

namespace physics {
	class CSphereCollider :
		public ACollider
	{
		glm::vec3 m_CenterPos;
		float     m_Radius;

	public:
		CSphereCollider(EObjectType ObjectType, TransformComponent* Transform, glm::vec3 CenterPos, float Radius);
		virtual ~CSphereCollider();

		virtual bool DetectCollider() override;
	};
}