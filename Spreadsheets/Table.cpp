#include "Table.h"


void Table::HandleColumnSizes(const Row& row)
{
	size_t rowSize = row.Size();
	if (rowSize > _columns)
	{
		_columns = rowSize;
		for (size_t row = 0; row < _rows; row++)
			if (container[row].Size() < rowSize)
				container[row].FillUpTo(rowSize);
	}
}

Table::Table(size_t rows) : _rows(rows)
{
	container = std::move(Vector<Row>(_rows));
}

Table::Table(size_t rows, size_t columns)
{
	_rows = rows;
	_columns = columns;
	for (size_t _row = 0; _row < _rows; _row++)
	{
		Row row(_columns);
		for (size_t column = 0; column < _columns; column++)
			row.AddCell(CellFactory::CreateCell(TextCell::EMPTY_VALUE));
		container.PushBack(std::move(row));
	}
}

size_t Table::Rows() const
{
    return _rows;
}

size_t Table::Columns() const
{
    return _columns;
}

Vector<Vector<UniquePtr<Cell>>> Table::Collection() const
{
	Vector<Vector<UniquePtr<Cell>>> vector;
	for (size_t i = 0; i < _rows; i++)
		vector.PushBack(std::move(container[i].Collection()));
	return vector;
}

void Table::AddRow(const Row& row)
{
	HandleColumnSizes(row);
	container.PushBack(row);
}

void Table::AddRow(Row&& row)
{
	HandleColumnSizes(row);
	container.PushBack(std::move(row));
}

void Table::AddRow()
{
	Row row(_columns); 
	for (size_t i = 0; i < _columns; i++)
		row.AddCell(CellFactory::CreateCell(TextCell::EMPTY_VALUE));
	container.PushBack(row);
}

void Table::AddColumn()
{
	size_t columnIndex = _columns++;
	for (size_t i = 0; i < Rows(); i++)
		container[i].AddCell(CellFactory::CreateCell(TextCell::EMPTY_VALUE));
}

void Table::InsertRowAt(size_t row)
{
	Row newRow(_columns);
	for (size_t i = 0; i < _columns; i++)
		newRow.AddCell(CellFactory::CreateCell(TextCell::EMPTY_VALUE));
	container.InsertAt(row, newRow);
}

void Table::InsertColumnAt(size_t column)
{
	for (size_t row = 0; row < _rows; row++)
		container[row].InsertCellAt
		(
			column, 
			CellFactory::CreateCell(TextCell::EMPTY_VALUE)
		);
}

void Table::InsertColumnAt(size_t column, const char* header)
{
	container[0].InsertCellAt
	(
		column,
		CellFactory::CreateCell(header)
	);

	for (size_t row = 1; row < _rows; row++)
		container[row].InsertCellAt
		(
			column, 
			CellFactory::CreateCell(TextCell::EMPTY_VALUE)
		);
}

const Row& Table::operator[](unsigned index) const
{
	return container[index];
}

Row& Table::operator[](unsigned index)
{
	return container[index];
}

std::ostream& operator<<(std::ostream& output, Table& table)
{
	Vector<Vector<String>> printTable;
	Vector<size_t> columnWidths;

	for (size_t row = 0; row < table.Rows(); row++)
	{
		Vector<String> tableRow;
		for (size_t column = 0; column < table.Columns(); column++)
		{
			try
			{
				tableRow.PushBack(table.container[row][column]->Evaluate(table.Collection()));
			}
			catch (std::runtime_error& ex)
			{
				tableRow.PushBack(ex.what());
			}
			catch (...)
			{
				tableRow.PushBack("ERROR");
			}

			if (row == 0)
			{
				columnWidths.PushBack(tableRow[column].Length());
			}
			else if (tableRow[column].Length() > columnWidths[column])
			{
				columnWidths[column] = tableRow[column].Length();
			}
		}
		printTable.PushBack(tableRow);
	}

	for (size_t row = 0; row < table.Rows(); row++)
	{
		output << "| ";
		for (size_t column = 0; column < table.Columns(); column++)
		{
			size_t spacesCount = columnWidths[column] - printTable[row][column].Length();

			switch (table[row][column]->DEFAULT_ALIGMENT())
			{
				case Cell::Alignment::Left:
					output << printTable[row][column];

					for (size_t i = 0; i < spacesCount; i++)
						output << ' ';
					break;

				case Cell::Alignment::Center:
					for (size_t i = 0; i < spacesCount / 2; i++)
						output << ' ';

					if (spacesCount % 2 == 1)
						output << ' ';

					output << printTable[row][column];

					for (size_t i = 0; i < spacesCount / 2; i++)
						output << ' ';
					break;

				case Cell::Alignment::Right:
					for (size_t i = 0; i < spacesCount; i++)
						output << ' ';

					output << printTable[row][column];
					break;
			}
			output << (column != table.Columns() - 1 ? " | " : "");
		}
		output << " |" << std::endl;
	}
	return output;
}