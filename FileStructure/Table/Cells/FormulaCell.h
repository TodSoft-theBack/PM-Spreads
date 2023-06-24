#pragma once
#include "Cell.h"

void ExtractRowNColumnAt(size_t& index, const String& value, int& row, int& columns);

class FormulaCell : public Cell
{
	private:
		String value;
		//To prevent self reference
		size_t row = -1, column = -1;
		String SubstituteTalbeReferences(const String& value, const Vector<Vector<UniquePtr<Cell>>>& referenceTable) const;

	public:
		FormulaCell() = default;
		FormulaCell(const String& string);
		Cell* Clone() const override;
		String ToString() const override;
		String Evaluate(const Vector<Vector<UniquePtr<Cell>>>& tableReference) const override;
		~FormulaCell() = default;
};

