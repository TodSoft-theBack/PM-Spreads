#include "Table.h"


void Table::HandleColumnSizes(const Row& row)
{
	size_t rowSize = row.Size();
	if (rowSize > _columns)
	{
		for (size_t i = _columns; i < rowSize; i++)
			maxWidthsPerColumn.PushBack(0);
		_columns = rowSize;
	}
}

Table::Table(size_t rows) : _rows(rows)
{
	container = std::move(Vector<Row>(_rows));
}

size_t Table::Rows() const
{
    return _rows;
}

size_t Table::Columns() const
{
    return _columns;
}

Vector<size_t>& Table::ColumnWidths()
{
	return maxWidthsPerColumn;
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

const Row& Table::operator[](unsigned index) const
{
	return container[index];
}

Row& Table::operator[](unsigned index)
{
	return container[index];
}

std::ostream& operator<<(std::ostream& output, const Table& table)
{
	for (size_t i = 0; i < table._rows; i++)
	{
		output << "| ";
		for (size_t j = 0; j < table._columns; j++)
		{
			String cell = table.container[i][j]->ToString(table.Collection());
			size_t spacesCount = 
				cell.Length() <= table.maxWidthsPerColumn[j] ? 
				table.maxWidthsPerColumn[j] - cell.Length() : 
				table.maxWidthsPerColumn[j];
			output << cell; 
			for (size_t space = 0; space < spacesCount; space++)
				output << ' ';
			output << (j != table._columns - 1 ? " | " : "");
		}
		output << " |" << std::endl;
	}
	return output;
}