#pragma once
#include "Vector.hpp"
#include "UniquePtr.hpp"
#include "Row.h"

class Table
{
	public:
	private:
		 Vector<Row> container;
		 Vector<unsigned> columnWidths;
		 size_t _rows = 0;
		 size_t _columns = 0;

	public:
		
		Table() = default;
		Table(size_t rows);
		size_t Rows() const;
		size_t Columns() const;
		Vector<Vector<UniquePtr<Cell>>> Collection() const;
		void AddRow(const Row& row);
		void AddRow(Row&& row);
		const Row& operator[](unsigned index) const;
		Row& operator[](unsigned index);
		friend std::ostream& operator<<(std::ostream& output, const Table& table);
};

