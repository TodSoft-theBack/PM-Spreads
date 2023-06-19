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
		String ToString(const Vector<Vector<UniquePtr<Cell>>>& reference) const override;
		~DecimalCell() = default;
};

