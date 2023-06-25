#include "DecimalCell.h"


DecimalCell::DecimalCell(const String& string)
{
	value = string.DecimalParse();
}

Cell* DecimalCell::Clone() const
{
	return new DecimalCell(*this);
}

Cell::Alignment DecimalCell::DEFAULT_ALIGMENT() const
{
	return Alignment::Right;
}

String DecimalCell::ToString() const
{
	return String::NumericString(value);
}

String DecimalCell::Evaluate(const Vector<Vector<UniquePtr<Cell>>>& reference) const
{
	return String::NumericString(value);
}
