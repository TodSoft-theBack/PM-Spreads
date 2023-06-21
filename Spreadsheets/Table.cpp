#include "Table.h"


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

Vector<Vector<UniquePtr<Cell>>> Table::Collection() const
{
	Vector<Vector<UniquePtr<Cell>>> vector;
	for (size_t i = 0; i < _rows; i++)
		vector.PushBack(std::move(container[i].Collection()));
	return vector;
}

void Table::AddRow(const Row& row)
{
	if (row.Size() > _columns)
		_columns = row.Size();

	container.PushBack(row);
}

void Table::AddRow(Row&& row)
{
	if (row.Size() > _columns)
		_columns = row.Size();
	container.PushBack(std::move(row));
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
			output << table.container[i][j]->ToString(table.Collection()) << (j != table._columns - 1 ? " | " : "");
		output << " |" << std::endl;
	}
	return output;
}