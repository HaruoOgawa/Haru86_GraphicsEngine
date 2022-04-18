#pragma once
#include <vector>
#include <memory>

namespace physics {
	class CCellContents;
	
	class CColliderCell
	{
		std::vector<std::shared_ptr<CCellContents>> m_CellContentsList;
	public:
		CColliderCell();
		virtual ~CColliderCell();

		bool SetCellContents(const std::shared_ptr<CCellContents>& CellContentsList);
		const std::vector<std::shared_ptr<CCellContents>>& GetCellContentsList()const;
	};
}