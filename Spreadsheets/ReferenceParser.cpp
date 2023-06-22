#include "ReferenceParser.h"

void ExtractRCAt(size_t index, size_t length, const String& value, size_t& row, size_t& columns)
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
}

String ReferenceParser::SubstituteTalbeReferences(const String& value, const Vector<Vector<UniquePtr<Cell>>>& referenceTable)
{
	String parsedString;
	size_t length = value.Length();
	int row = -1, column = -1;
	for (size_t i = 0; i < length;)
	{
		if (value[i] == 'R')
		{
			size_t row, columns;
			ExtractRCAt(i, length, value, row, columns);

		}
		else
			i++;
		parsedString += value[i];

	}
	std::cout << parsedString << std::endl;
    return parsedString;
}
