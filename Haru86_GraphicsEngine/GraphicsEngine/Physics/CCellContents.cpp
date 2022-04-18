#include "CCellContents.h"
#include "ACollider.h"
#include "CColliderCell.h"

namespace physics {
	CCellContents::CCellContents(const std::shared_ptr<ACollider>& Collider) :
		m_Collider(Collider),
		m_ColliderCell(nullptr),
		m_NextCellContents(nullptr),
		m_PreCellContents(nullptr)
	{
	}

	CCellContents::~CCellContents() {

	}

	const std::shared_ptr<ACollider>& CCellContents::GetCollider()const {
		return m_Collider;
	}

	//
	CColliderCell* CCellContents::GetColliderCell()const {
		return m_ColliderCell;
	}

	void CCellContents::SetColliderCell(CColliderCell* ColliderCell){
		m_ColliderCell = ColliderCell;
	}

	//
	void CCellContents::SetPreCellContents(CCellContents* CellContents){
		m_PreCellContents = CellContents;
	}

	CCellContents* CCellContents::GetPreCellContents()const {
		return m_PreCellContents;
	}

	void CCellContents::SetNextCellContents(CCellContents* CellContents) {
		m_NextCellContents = CellContents;
	}

	CCellContents* CCellContents::GetNextCellContents()const {
		return m_NextCellContents;
	}
}