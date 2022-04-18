#include "CColliderCell.h"
#include "CCellContents.h"

namespace physics {
	CColliderCell::CColliderCell() :
		m_LatestCellContents(nullptr)
	{
	}

	CColliderCell::~CColliderCell() {
		m_CellContentsList.clear();
	}

	bool CColliderCell::SetCellContents(const std::shared_ptr<CCellContents>& CellContents) {
		//
		if (!CellContents->GetCollider())return false;
		
		// ƒZƒ‹‚ª“¯ˆê‚È‚ç“o˜^‚µ‚È‚¢
		if (CellContents->GetColliderCell() == this)return false;

		if (!m_LatestCellContents) {
			m_LatestCellContents = CellContents.get();
		}
		else {
			CellContents->SetNextCellContents(m_LatestCellContents);
			m_LatestCellContents->SetPreCellContents(CellContents.get());
			m_LatestCellContents = CellContents.get();
		}

		// ƒZƒ‹‚ðƒZƒ‹ƒRƒ“ƒeƒ“ƒc‚É“o˜^
		CellContents->SetColliderCell(this);
		//m_CellContentsList.push_back(CellContents);

		return true;
	}

	const std::vector<std::shared_ptr<CCellContents>>& CColliderCell::GetCellContentsList()const {
		return m_CellContentsList;
	}

}