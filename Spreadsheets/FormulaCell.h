#pragma once
#include "Cell.h"
#include "String.h"

class FormulaCell : public Cell
{
	private:
		String value;
	public:
		FormulaCell() = default;
		FormulaCell(const String& string);
		Cell* Clone() const override;
		String ToString(const Vector<Vector<UniquePtr<Cell>>>& reference) const override;
		~FormulaCell() = default;
};

