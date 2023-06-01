#pragma once
#include "Cell.h"

class CellFactory
{
	public:
		static Cell* CreateCell(const char* value);
};

