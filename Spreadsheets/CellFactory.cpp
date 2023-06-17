#include "CellFactory.h"
#include "TextCell.h"

Cell* CellFactory::CreateCell(const char* value)
{
    String parser = value;
    parser.Trim();
    /*if (parser.IsInteger())
        return new IntegerCell(parser);
    else if (parser.IsDecimal())
        return new DecimalCell(parser);
    else if (parser[0] == '=')
        return new FormulaCell(parser);*/

    return new TextCell(value);
}
