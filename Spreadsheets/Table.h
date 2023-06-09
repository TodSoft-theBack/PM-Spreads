#pragma once
#include "Vector.hpp"
#include "UniquePtr.hpp"
#include "Row.h"

class Table
{
	private:
		Vector<Row> container;
		size_t _rows = 0;
		size_t _columns = 0;
		void HandleColumnSizes(const Row& row);

	public:
		Table() = default;
		Table(size_t rows);
		Table(size_t rows, size_t columns);
		size_t Rows() const;
		size_t Columns() const;
		Vector<Vector<UniquePtr<Cell>>> Collection() const;
		void AddRow(const Row& row);
		void AddRow(Row&& row);
		void AddRow();
		void AddColumn();
		void InsertRowAt(size_t row);
		void InsertColumnAt(size_t column);
		void InsertColumnAt(size_t column, const char* header);
		const Row& operator[](unsigned index) const;
		Row& operator[](unsigned index);
		friend std::ostream& operator<<(std::ostream& output, Table& table);
};

