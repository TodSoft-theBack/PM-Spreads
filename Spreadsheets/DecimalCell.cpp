#include "DecimalCell.h"


DecimalCell::DecimalCell(const String& string)
{
	value = string.DecimalParse();
}

Cell* DecimalCell::Clone() const
{
	return new DecimalCell(*this);
}

String DecimalCell::ToString(const Vector<Vector<std::unique_ptr<Cell>>>& reference) const
{
	return String::NumericString(value);
}
