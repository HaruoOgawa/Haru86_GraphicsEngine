#pragma once
#include "./ICollider.h"
#include "EObjectType.h"
#include "EColliderType.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>

class TransformComponent;

namespace physics {
	struct SCollisionInfo
	{
		float m_depth;
		glm::vec3 m_normal;
	public:
		SCollisionInfo(float depth, glm::vec3 normal);
	};

	class ACollider
	{
		EObjectType m_ObjectType;
		EColliderType m_ColliderType;
		TransformComponent* m_Transform;
		glm::vec3 m_Force;
		glm::vec3 m_Velocity;
		float     m_Mass;

	public:
		ACollider(EObjectType ObjectType, EColliderType ColliderType, TransformComponent* Transform);
		virtual ~ACollider();

		EObjectType GetObjectType()const;
		EColliderType GetColliderType()const;

		std::shared_ptr<SCollisionInfo> DetectCollider(std::shared_ptr<ACollider> Collider);
		virtual std::shared_ptr<SCollisionInfo> DetectBoxCollider(std::shared_ptr<ACollider> Collider) = 0;
		virtual std::shared_ptr<SCollisionInfo> DetectSphereCollider(std::shared_ptr<ACollider> Collider) = 0;

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
