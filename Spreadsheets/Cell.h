#pragma once
#include "String.h"


class Cell
{
	public:
		virtual String ToString(const Vector<Vector<std::unique_ptr<Cell>>>& reference) const = 0;
		virtual Cell* Clone() const = 0;
		virtual ~Cell() = default;
};

