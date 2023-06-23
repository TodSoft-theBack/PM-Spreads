#include "Cell.h"

bool Cell::HasError() const
{
    return hasError;
}

bool& Cell::HasError()
{
    return hasError;
}
