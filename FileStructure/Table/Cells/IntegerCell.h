#pragma once
#include "Cell.h"

class IntegerCell : public Cell
{
	private:
		int value = 0;
	public:

		IntegerCell() = default;
		IntegerCell(const String& string);
		Cell* Clone() const override;
		String ToString() const override;
		String Evaluate(const Vector<Vector<UniquePtr<Cell>>>& tableReference) const override;
		~IntegerCell() = default;

};

