#include "TextCell.h"

TextCell::TextCell(const char* value) : value(value)
{
}

Cell* TextCell::Clone() const
{
    return new TextCell(*this);
}

String TextCell::ToString(const Vector<Vector<UniquePtr<Cell>>>& reference) const
{
    return value;
}
