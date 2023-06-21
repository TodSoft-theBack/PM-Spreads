#include "ReferenceParser.h"

String ReferenceParser::SubstituteTalbeReferences(const String& value, const Vector<Vector<UniquePtr<Cell>>>& referenceTable)
{
	String parsedString;
	size_t length = value.Length();
	int row = -1, column = -1;
	for (size_t i = 0; i < length; i++)
	{
		if (value[i] == 'R')
		{
			unsigned rowEndIndex = i;
			for (size_t j = i + 1; j < length; j++)
				if (value[j] == 'C')
				{
					rowEndIndex = j;
					break;
				}
			row = value.Substring(i+1, rowEndIndex - i - 1).IntegerParse();
			unsigned columnEndIndex = rowEndIndex;
			for (size_t j = rowEndIndex + 1; j < length; j++)
				if (!String::IsDigit(value[j]))
				{
					columnEndIndex = j;
					break;
				}
			column = value.Substring(rowEndIndex + 1, columnEndIndex - rowEndIndex - 1).IntegerParse();
			i = columnEndIndex;

			parsedString += referenceTable[row][column]->ToString(referenceTable);
		}
		parsedString += value[i];
	}
    return parsedString;
}
