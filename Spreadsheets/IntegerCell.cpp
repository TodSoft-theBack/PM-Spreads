#include "IntegerCell.h"

IntegerCell::IntegerCell(const String& string)
{
	value = string.IntegerParse();
}

Cell* IntegerCell::Clone() const
{
	return new IntegerCell(*this);
}

Cell::Alignment IntegerCell::DEFAULT_ALIGMENT() const
{
	return Alignment::Right;
}

String IntegerCell::ToString() const
{
	return String::NumericString(value);
}

String IntegerCell::Evaluate(const Vector<Vector<UniquePtr<Cell>>>& reference) const
{
	return String::NumericString(value);
}
