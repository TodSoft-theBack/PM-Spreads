#include "TextCell.h"

const char* TextCell::EMPTY_VALUE = "\"\"";

TextCell::TextCell(const char* value)
{
    size_t length = strlen(value);
    if (length <= 2)
        return;
    this->value = String(length - 2);
    for (size_t i = 1; i < length - 1; i++)
        this->value[i - 1] = value[i];
    this->value[length - 2] = '\0';
}

Cell* TextCell::Clone() const
{
    return new TextCell(*this);
}

String TextCell::ToString(const Vector<Vector<UniquePtr<Cell>>>& reference)
{
    return value;
}
