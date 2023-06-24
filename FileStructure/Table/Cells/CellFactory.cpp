#include "CellFactory.h"
#include "TextCell.h"
#include "IntegerCell.h"
#include "DecimalCell.h"
#include "FormulaCell.h"

Cell* CellFactory::CreateCell(const char* value)
{
    String parser = String::Trim(value);
    if (parser.IsEmpty())
        return new TextCell();
    if (parser.First() == '\"' && parser.Last() == '\"')
        return new TextCell(value);
    if (parser.First() == '=')
        return new FormulaCell(parser);

    String::NumericType type = parser.CheckType();
    switch (type)
    {
        case String::NumericType::Integer:
            return new IntegerCell(std::move(parser));
        case String::NumericType::Decimal:
            return new DecimalCell(std::move(parser));
    }

    throw std::runtime_error("Invalid data type!!!");
}
