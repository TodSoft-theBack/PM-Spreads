#pragma once
#include "Cells/CellFactory.h"
#include "Cells/Cell.h"

class Row
{
	private:
		static const size_t DEFAULT_CAPACITY = 8;

	public:
		static Row ParseLine(const String& line, size_t rowIndex);
		static Row ParseLine(const String& line, size_t rowIndex, size_t columnCount);

	private:
		Cell** container = nullptr;
		size_t _count = 0;
		size_t _capacity = DEFAULT_CAPACITY;

		void CopyMemberData(const Row& copy);
		void FreeMemberData();
		void MoveMemberData(Row&& temporary) noexcept;
		void Resize(size_t size);

	public:
		Row();
		Row(size_t capacity);
		Row(const Row& copy);
		Row(Row&& temporary) noexcept;
		size_t Size() const;
		void AddCell(Cell* cell);
		Row& operator=(const Row& row);
		Row& operator=(Row&& row) noexcept;
		Vector<UniquePtr<Cell>> Collection() const;
		const Cell* operator[](unsigned index) const;
		Cell*& operator[](unsigned index);
		bool IsEmpty() const;
		~Row();
};

