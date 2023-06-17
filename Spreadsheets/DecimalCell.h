#pragma once
#include "Cell.h"
#include "String.h"
#include "Table.h"

class DecimalCell : public Cell
{
	private:
		double value;

	public:
		DecimalCell() = default;
		DecimalCell(const String& string);
		Cell* Clone() const override;
		String ToString() const override;
		~DecimalCell() = default;
};

