#pragma once
#include "./ICollider.h"
#include "EObjectType.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>

class TransformComponent;

namespace physics {
	class ACollider
	{
		EObjectType m_ObjectType;
		std::shared_ptr<TransformComponent> m_Transform;
	public:
		ACollider(EObjectType ObjectType,std::shared_ptr<TransformComponent> Transform);
		virtual ~ACollider();

		virtual bool DetectCollider() = 0;

	private:

	};
}
