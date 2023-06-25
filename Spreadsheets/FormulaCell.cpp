#include "FormulaCell.h"
#include "ExpressionParser.h"

void ExtractRowNColumnAt(size_t& index, const String& value, int& row, int& columns)
{
	String _row, _column;
	bool collectingRow = true, collectingColumn = false;

	size_t current = index + 1, length = value.Length();
	for (; current < length; current++)
	{
		if (value[current] == 'C')
		{
			collectingRow = false;
			collectingColumn = true;
			continue;
		}

		if (collectingRow)
		{
			_row += value[current];
			continue;
		}

		if (!String::IsDigit(value[current]))
			break;

		if (collectingColumn)
			_column += value[current];
	}

	index = current;
	row = _row.IntegerParse();
	columns = _column.IntegerParse();
}

String FormulaCell::SubstituteTalbeReferences(const String& value, const Vector<Vector<UniquePtr<Cell>>>& referenceTable) const
{
	Vector<char> substitutedString;
	size_t length = value.Length();

	for (size_t current = 0; current < length; current++)
	{
		if (value[current] == 'R')
		{
			int row = -1, column = -1;
			ExtractRowNColumnAt(current, value, row, column);
			if (row < 1 || column < 1)
				throw std::runtime_error("Table indecies are 1-based!");

			if (referenceTable[row - 1][column - 1].Value() == this)
				throw std::runtime_error("Self reference!");

			if (row - 1 > referenceTable.Count() || column - 1 > referenceTable[row - 1].Count())
			{
				substitutedString.PushBack('0');
				continue;
			}

			String cell = referenceTable[row - 1][column - 1]->Evaluate(referenceTable);
			String::NumericType type = cell.CheckType();
			switch (type)
			{
				case String::NumericType::Integer:
				case String::NumericType::Decimal:
					for (char digit : cell)
						substitutedString.PushBack(digit);
					break;

				default:
					substitutedString.PushBack('0');
					break;
			}
			continue;
		}
		else
			substitutedString.PushBack(value[current]);

	}
	return substitutedString;
}

FormulaCell::FormulaCell(const String& string) : value(string) { }

Cell* FormulaCell::Clone() const
{
	return new FormulaCell(*this);
}

Cell::Alignment FormulaCell::DEFAULT_ALIGMENT() const
{
	return Alignment::Center;
}

String FormulaCell::ToString() const
{
	return value;
}

String FormulaCell::Evaluate(const Vector<Vector<UniquePtr<Cell>>>& reference) const
{
	return ExpressionParser::ParseExpression
	(
		SubstituteTalbeReferences(value, reference)
		.Substring(1)
	)
	->Evaluate()
	->GetResult();
}
