#include "TextCell.h"

const char* TextCell::EMPTY_VALUE = "\"\"";

TextCell::TextCell(const char* value)
{
    this->value = String::GetFromString(value);
}

Cell* TextCell::Clone() const
{
    return new TextCell(*this);
}

String TextCell::ToString() const
{
    return value;
}

String TextCell::Evaluate(const Vector<Vector<UniquePtr<Cell>>>& reference) const
{
    return value;
}
