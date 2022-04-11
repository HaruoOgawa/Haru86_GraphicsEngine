#pragma once
#include <vector>
#include <memory>
#include "EColliderType.h"
#include "EObjectType.h"
#include <glm/glm.hpp>
class GameObject;
class Primitive;

namespace physics {
	class ACollider;

	class CColliderTree
	{
		std::vector<std::shared_ptr<ACollider>> m_ColliderList;
	public:
		CColliderTree();
		virtual ~CColliderTree();

		bool AddCollider(EColliderType ColliderType, EObjectType ObjectType, GameObject* Obj);
		bool MakeColliderTree();

		std::vector<std::shared_ptr<ACollider>> GetPassiveColliderListFromTree(std::shared_ptr<ACollider> Collider);

		const std::vector<std::shared_ptr<ACollider>>& GetColliderList()const;
	private:
		bool CreateSphereCollider(const std::vector<std::shared_ptr<Primitive>>& PrimitiveList, GameObject* Obj, EObjectType ObjectType, EColliderType ColliderType);
		bool CreateSimpleBoxCollider(const std::vector<std::shared_ptr<Primitive>>& PrimitiveList, GameObject* Obj, EObjectType ObjectType, EColliderType ColliderType);
		bool CreateBoxCollider(const std::vector<std::shared_ptr<Primitive>>& PrimitiveList, GameObject* Obj, EObjectType ObjectType, EColliderType ColliderType);

		bool CalculateAABB(const std::vector<float>& Vertices,glm::vec3& CenterPos, glm::vec3& MaxPos, glm::vec3& MinPos);

		bool CalculateSphereVolumeFromAABB(const std::vector<float>& Vertices, glm::vec3& CenterPos , float& Radius);
		bool OptimizeSphereVolume();

		bool CalculateOBB();
		bool OptimizeOBB();
	};
}



