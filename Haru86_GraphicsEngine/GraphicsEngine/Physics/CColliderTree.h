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
	class CColliderCell;

	class CColliderTree
	{
		std::vector<std::shared_ptr<ACollider>> m_ColliderList;

		int MAXCELLLEVEL;

		float m_TreeMin;
		float m_TreeMax;

		int m_SizeCellNum;
		float m_CellSize;

		std::vector<int> m_CellCountPerLevel;
		std::vector<CColliderCell> m_CellList;

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

		//
		bool MakeTree();

		//
		unsigned int GetCellIndexFromMortonNumber(const glm::vec3& MinPos, const glm::vec3& MaxPos)const;
		unsigned int GetMortonNumber(unsigned long x, unsigned long y, unsigned long z)const;
		unsigned int SeparateBitForMorton(unsigned long val)const;
	};
}



