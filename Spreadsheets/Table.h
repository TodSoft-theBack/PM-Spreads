#pragma once
#include "Vector.hpp"
#include "Row.h"

class Table
{
	public:
	private:
		 Vector<Row> container;
		 size_t _rows = 0;
		 size_t _columns = 0;

	public:
		
		Table() = default;
		Table(size_t rows, size_t columns);
		size_t Rows() const;
		size_t Columns() const;
		Vector<Vector<std::unique_ptr<Cell>>> Collection() const;
		const Row& operator[](unsigned index) const;
		Row& operator[](unsigned index);
		friend std::ostream& operator<<(std::ostream& output, const Table& table);
};

