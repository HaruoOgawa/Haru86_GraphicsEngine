#include "CColliderCell.h"
#include "CCellContents.h"

namespace physics {
	CColliderCell::CColliderCell() {

	}

	CColliderCell::~CColliderCell() {
		m_CellContentsList.clear();
	}

	bool CColliderCell::SetCellContents(const std::shared_ptr<CCellContents>& CellContentsList) {
		m_CellContentsList.push_back(CellContentsList);

		return true;
	}

	const std::vector<std::shared_ptr<CCellContents>>& CColliderCell::GetCellContentsList()const {
		return m_CellContentsList;
	}

}