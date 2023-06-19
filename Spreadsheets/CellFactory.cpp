#include "CellFactory.h"
#include "TextCell.h"
#include "IntegerCell.h"
#include "DecimalCell.h"
#include "FormulaCell.h"

Cell* CellFactory::CreateCell(const String& value)
{
    String parser = String::Trim(value);
    if (parser.IsInteger())
        return new IntegerCell(parser);
    else if (parser.IsDecimal())
        return new DecimalCell(parser);
    else if (parser[0] == '=')
        return new FormulaCell(parser);

    return new TextCell(value);
}
