#include "ReferenceParser.h"

void ExtractRCAt(size_t& index, size_t length, const String& value, int& row, int& columns)
{
	String _row, _column;
	size_t rowIndex = index + 1, columnIndex = index + 1;
	for (size_t j = index + 1; j < length; j++)
	{
		if (value[j] == 'C')
		{
			columnIndex = j + 1;
			_row = value.Substring(rowIndex, j - index);
		}

		if (!String::IsDigit(value[j]))
			_column = value.Substring(columnIndex, columnIndex - j);
	}
	row = _row.IntegerParse();
	columns = _column.IntegerParse();

	index = columnIndex;
}

String ReferenceParser::SubstituteTalbeReferences(const String& value, const Vector<Vector<UniquePtr<Cell>>>& referenceTable)
{
	String parsedString;
	size_t length = value.Length();
	
	for (size_t i = 0; i < length;)
	{
		if (value[i] == 'R')
		{
			int row = -1, column = -1;
			ExtractRCAt(i, length, value, row, column);
			if (row == -1 || column == -1)
				throw std::runtime_error("Invalid Reference");
			String cell = referenceTable[row][column].Value()->ToString(referenceTable);
			String::NumericType type = cell.CheckType();

			switch (type)
			{
				case String::NumericType::Integer:
				case String::NumericType::Decimal:
					parsedString += cell;
					break;
				default:
					parsedString += '0';
					break;
			}
			
		}
		else
			i++;
		parsedString += value[i];

	}
	std::cout << parsedString << std::endl;
    return parsedString;
}
