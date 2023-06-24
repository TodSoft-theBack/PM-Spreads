#include "IntegerCell.h"

IntegerCell::IntegerCell(const String& string)
{
	value = string.IntegerParse();
}

Cell* IntegerCell::Clone() const
{
	return new IntegerCell(*this);
}

String IntegerCell::ToString() const
{
	return String::NumericString(value);
}

String IntegerCell::Evaluate(const Vector<Vector<UniquePtr<Cell>>>& reference) const
{
	return String::NumericString(value);
}
