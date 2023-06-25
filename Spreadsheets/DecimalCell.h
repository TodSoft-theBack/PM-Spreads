#pragma once
#include "Cell.h"
#include "String.h"
#include "Table.h"

class DecimalCell : public Cell
{
	private:
		double value = 0.0;

	public:
		DecimalCell() = default;
		DecimalCell(const String& string);
		Cell* Clone() const override;
		Alignment DEFAULT_ALIGMENT() const override;
		String ToString() const override;
		String Evaluate(const Vector<Vector<UniquePtr<Cell>>>& tableReference) const override;
		~DecimalCell() = default;
};

