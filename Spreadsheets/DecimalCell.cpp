#include "DecimalCell.h"


DecimalCell::DecimalCell(const String& string)
{
	value = string.DecimalParse();
}

Cell* DecimalCell::Clone() const
{
	return new DecimalCell(*this);
}

String DecimalCell::ToString(const Vector<Vector<UniquePtr<Cell>>>& reference)
{
	return String::NumericString(value);
}
