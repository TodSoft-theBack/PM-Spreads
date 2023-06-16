#pragma once
#include <iostream>
#include "String.h"

class Cell
{
	public:
		virtual String ToString() const = 0;
		virtual Cell* Clone() const = 0;
		virtual ~Cell() = default;
};

