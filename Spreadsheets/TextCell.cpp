#include "TextCell.h"

const char* TextCell::EMPTY_VALUE = "\"\"";

TextCell::TextCell(const char* value) : value(value) { }

Cell* TextCell::Clone() const
{
    return new TextCell(*this);
}

String TextCell::ToString(const Vector<Vector<UniquePtr<Cell>>>& reference) const
{
    size_t length = value.Length();
    String result(length >= 2 ? length - 2 : 0);
    if (!result.IsEmpty())
        for (size_t i = 1; i < length - 1; i++)
            result[i - 1] = value[i];
    return result;
}
