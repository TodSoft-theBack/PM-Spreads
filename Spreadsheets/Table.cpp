#include "Table.h"

Table::Table(size_t rows, size_t columns) : _rows(rows), _columns(columns)
{
	for (size_t i = 0; i < rows; i++)
	{
		container.PushBack(std::move(Vector<Cell*>(columns)));
		for (size_t j = 0; j < columns; j++)
			container[i].PushBack(std::move(nullptr));
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

void Table::AppendRow(const Vector<Cell*>& row)
{
	container.PushBack(row);
}

void Table::AppendRow(Vector<Cell*>&& row)
{
	container.PushBack(std::move(row));
}

const Cell* Table::CellAt(unsigned row, unsigned column) const
{
	return container[row][column];
}

std::ostream& operator<<(std::ostream& output, const Table& table)
{
	for (size_t i = 0; i < table._rows; i++)
	{
		output << "| ";
		for (size_t j = 0; j < table._columns; j++)
			output << table.container[i][j] << (j != table._columns - 1 ? " | " : "");
		output << " |" << std::endl;
	}
	return output;
}
