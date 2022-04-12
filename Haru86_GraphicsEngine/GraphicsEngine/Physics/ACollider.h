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
		bool m_IsCollided;
		float m_depth;
		glm::vec3 m_normal; // normal‚Í”½”­‚·‚é•ûŒü
	public:
		SCollisionInfo(bool IsCollided,float depth, glm::vec3 normal);
	};

	class ACollider
	{
	public:
		ACollider(EObjectType ObjectType, EColliderType ColliderType, TransformComponent* Transform);
		virtual ~ACollider();

		EObjectType GetObjectType()const;
		EColliderType GetColliderType()const;

		std::shared_ptr<SCollisionInfo> DetectCollider(std::shared_ptr<ACollider> Collider);
		
		virtual bool CalcIsingCollided(glm::vec3 CollidedNormal, float CollidedDepth)=0;

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

	protected:
		EObjectType m_ObjectType;
		EColliderType m_ColliderType;
		TransformComponent* m_Transform;
		glm::vec3 m_Force;
		glm::vec3 m_Velocity;
		float     m_Mass;
	};
}
