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
    size_t length = value.Length() + 2;
    String result(length);
    result[0] = '\"';
    for (size_t i = 1; i < length - 1; i++)
        result[i] = value[i - 1];
    result[length - 1] = '\"';
    return result;
}

Cell::Alignment TextCell::DEFAULT_ALIGMENT() const
{
    return Alignment::Left;
}


String TextCell::Evaluate(const Vector<Vector<UniquePtr<Cell>>>& reference) const
{
    return value;
}
