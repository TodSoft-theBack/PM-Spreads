#pragma once
#include "UniquePtr.hpp"
#include "String.h"

class Cell
{
	protected:
		bool hasError = false;

	public:
		bool HasError() const;
		bool& HasError();
		virtual String ToString(const Vector<Vector<UniquePtr<Cell>>>& reference) = 0;
		virtual Cell* Clone() const = 0;
		virtual ~Cell() = default;
};

