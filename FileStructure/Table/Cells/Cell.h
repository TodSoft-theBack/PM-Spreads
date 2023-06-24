#pragma once
#include "../../Generic/String.h"
#include "../../Generic/Vector.hpp"
#include "../../Generic/UniquePtr.hpp"


class Cell
{
	public:
		virtual String ToString() const = 0;
		virtual String Evaluate(const Vector<Vector<UniquePtr<Cell>>>& tableReference) const = 0;
		virtual Cell* Clone() const = 0;
		virtual ~Cell() = default;
};

