#pragma once
#include "UniquePtr.hpp"
#include "String.h"

class Cell
{
	public:
		enum struct Alignment 
		{
			Left,
			Center,
			Right
		};
	public:
		virtual Alignment DEFAULT_ALIGMENT() const = 0;
		virtual String ToString() const = 0;
		virtual String Evaluate(const Vector<Vector<UniquePtr<Cell>>>& tableReference) const = 0;
		virtual Cell* Clone() const = 0;
		virtual ~Cell() = default;
};

