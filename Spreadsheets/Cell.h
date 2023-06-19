#pragma once
#include "UniquePtr.hpp"
#include "String.h"

class Cell
{
	public:
		virtual String ToString(const Vector<Vector<UniquePtr<Cell>>>& reference) const = 0;
		virtual Cell* Clone() const = 0;
		virtual ~Cell() = default;
};

