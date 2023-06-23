#pragma once
#include "Cell.h"
#include "String.h"

class FormulaCell : public Cell
{
	private:
		String value;
		//To prevent self reference
		size_t row = -1, column = -1;
		String SubstituteTalbeReferences(const String& value, const Vector<Vector<UniquePtr<Cell>>>& referenceTable);
	public:
		FormulaCell() = default;
		FormulaCell(const String& string);
		Cell* Clone() const override;
		String ToString(const Vector<Vector<UniquePtr<Cell>>>& reference) override;
		~FormulaCell() = default;
};

