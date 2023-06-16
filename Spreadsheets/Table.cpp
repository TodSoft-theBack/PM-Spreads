#include "Table.h"

Table::Table(size_t rows, size_t columns) : _rows(rows), _columns(columns)
{
	container = std::move(Vector<Row>(_rows));
	for (size_t i = 0; i < rows; i++)
		container.PushBack(std::move(Row(_columns)));
}

size_t Table::Rows() const
{
    return _rows;
}

size_t Table::Columns() const
{
    return _columns;
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
			output << table.container[i][j]->ToString() << (j != table._columns - 1 ? " | " : "");
		output << " |" << std::endl;
	}
	return output;
}