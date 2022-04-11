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
		TransformComponent* m_Transform;
		glm::vec3 m_Force;
		glm::vec3 m_Velocity;
		float     m_Mass;

	public:
		ACollider(EObjectType ObjectType, TransformComponent* Transform);
		virtual ~ACollider();

		EObjectType GetObjectType()const;

		virtual bool DetectCollider() = 0;

		void SetForce(glm::vec3 Force);
		const glm::vec3& GetForce()const;
		
		void SetVelocity(glm::vec3 Velocity);
		const glm::vec3& GetVelocity()const;

		void SetMass(float Mass);
		float GetMass()const;

		TransformComponent* GetTransform();

	private:

	};
}
