#include "FormulaCell.h"
#include "ExpressionParser.h"

void ExtractRCAt(size_t& index, size_t length, const String& value, int& row, int& columns)
{
	String _row, _column;
	bool collectingRow = true, collectingColumn = false;
	size_t j = index + 1;
	for (; j < length; j++)
	{
		if (value[j] == 'C')
		{
			collectingRow = false;
			collectingColumn = true;
			continue;
		}

		if (collectingRow)
		{
			_row += value[j];
			continue;
		}

		if (!String::IsDigit(value[j]))
		{
			index = j;
			break;
		}

		if (collectingColumn)
			_column += value[j];
	}
	if (j == length)
		index = length;
	row = _row.IntegerParse();
	columns = _column.IntegerParse();
}

String FormulaCell::SubstituteTalbeReferences(const String& value, const Vector<Vector<UniquePtr<Cell>>>& referenceTable)
{
	Vector<char> parsedString;
	size_t length = value.Length();

	for (size_t i = 0; i < length; i++)
	{
		if (value[i] == 'R')
		{
			int row = -1, column = -1;
			ExtractRCAt(i, length, value, row, column);
			if (row < 1 || column < 1)
				throw std::runtime_error("Table indecies are 1-based!");
			if (referenceTable[row - 1][column - 1].Value() == this)
			{
				hasError = true;
				throw std::runtime_error("Self reference!");
			}

			if (referenceTable[row - 1][column - 1].Value()->HasError())
				return "ERROR";
			String cell = referenceTable[row - 1][column - 1].Value()->ToString(referenceTable);
			String::NumericType type = cell.CheckType();

			switch (type)
			{
			case String::NumericType::Integer:
			case String::NumericType::Decimal:
				for (char digit : cell)
					parsedString.PushBack(digit);
				break;
			default:
				parsedString.PushBack('0');
				break;
			}
			continue;
		}
		else
			parsedString.PushBack(value[i]);

	}
	return parsedString;
}

FormulaCell::FormulaCell(const String& string) : value(string)
{
}

Cell* FormulaCell::Clone() const
{
	return new FormulaCell(*this);
}

String FormulaCell::ToString(const Vector<Vector<UniquePtr<Cell>>>& reference)
{
	return ExpressionParser::ParseExpression
	(
		SubstituteTalbeReferences(value, reference)
		.Substring(1)
	)
	->Evaluate()
	->GetResult();
}
