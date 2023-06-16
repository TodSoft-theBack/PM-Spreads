#include "CellFactory.h"

Cell* CellFactory::CreateCell(const char* value)
{
    return new TextCell(value);
}
