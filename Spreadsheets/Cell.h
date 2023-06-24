#pragma once
#include "UniquePtr.hpp"
#include "String.h"

class Cell
{
	public:
		virtual String ToString() const = 0;
		virtual String Evaluate(const Vector<Vector<UniquePtr<Cell>>>& tableReference) const = 0;
		virtual Cell* Clone() const = 0;
		virtual ~Cell() = default;
};

