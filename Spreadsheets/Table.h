#pragma once
#include "Vector.hpp"
#include "UniquePtr.hpp"
#include "Row.h"

class Table
{
	public:
		static const size_t DEFAULT_COLUMNS = 0;

	private:
		Vector<Row> container;
		Vector<size_t> maxWidthsPerColumn;
		size_t _rows = 0;
		size_t _columns = DEFAULT_COLUMNS;
		void HandleColumnSizes(const Row& row);

	public:
		Table() = default;
		Table(size_t rows);
		Table(size_t rows, size_t columns);
		size_t Rows() const;
		size_t Columns() const;
		Vector<size_t>& ColumnWidths();
		Vector<Vector<UniquePtr<Cell>>> Collection() const;
		void AddRow(const Row& row);
		void AddRow(Row&& row);
		void AddRow();
		const Row& operator[](unsigned index) const;
		Row& operator[](unsigned index);
		friend std::ostream& operator<<(std::ostream& output, const Table& table);
};

