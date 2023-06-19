#pragma once
#include "Cell.h"
#include "TextCell.h"

class CellFactory
{
	public:
		static Cell* CreateCell(const String& value);
};

