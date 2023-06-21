#pragma once
#include "Cell.h"
#include "String.h"

class TextCell : public Cell
{
	public:
		static const char* EMPTY_VALUE;
	private:
		String value = EMPTY_VALUE;
	public:
		TextCell() = default;
		TextCell(const char* value);
		Cell* Clone() const override;
		String ToString(const Vector<Vector<UniquePtr<Cell>>>& reference) const override;
		~TextCell() = default;
};

