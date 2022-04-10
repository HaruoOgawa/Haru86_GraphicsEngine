#pragma once
#include "ACollider.h"

namespace physics {
	class CBoxCollider :
		public ACollider
	{
		glm::vec3			   m_CenterPos;
		std::vector<glm::vec3> m_LocalAxis;
		glm::vec3              m_LocalAxisSize;
		
	public:
		CBoxCollider(EObjectType ObjectType, TransformComponent* Transform,
			glm::vec3 CenterPos, std::vector<glm::vec3> LocalAxis, glm::vec3 LocalAxisSize);
		virtual ~CBoxCollider();

		virtual bool DetectCollider() override;
	};
}


