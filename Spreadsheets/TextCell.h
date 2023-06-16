#pragma once
#include "Cell.h"
#include "String.h"

class TextCell : public Cell
{
	private:
		String value;
	public:
		TextCell() = default;
		TextCell(const char* value);
		Cell* Clone() const override;
		String ToString() const override;
		~TextCell() = default;
};

