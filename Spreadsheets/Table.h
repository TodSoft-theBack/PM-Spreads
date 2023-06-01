#pragma once
#include "Cell.h"
#include "Vector.hpp"

class Table
{
	private:
		 Vector<Vector<Cell*>> container;
		 size_t _rows = 0;
		 size_t _columns = 0;

	public:
		Table() = default;
		Table(size_t rows, size_t columns);
		size_t Rows() const;
		size_t Columns() const;
		void AppendRow(const Vector<Cell*>& row);
		void AppendRow(Vector<Cell*>&& row);
		friend std::ostream& operator<<(std::ostream& output, const Table& table);
};

