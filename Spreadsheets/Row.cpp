#include "Row.h"


Row Row::ParseLine(const String& line, size_t columnCount)
{
	if (line.Length() == 0)
		return Row();
	Vector<String> values = line.Split(',');
	size_t count = values.Count();
	Row result;
	for (size_t i = 0; i < count; i++)
		result.AddCell(CellFactory::CreateCell(String::Trim(values[i])));

	if (count < columnCount)
		for (size_t i = count; i < columnCount; i++)
			result.AddCell(CellFactory::CreateCell(TextCell::EMPTY_VALUE));

	return result;
}

void Row::CopyMemberData(const Row& copy)
{
	_capacity = copy._capacity;
	_count = copy._count;
	container = new Cell* [_capacity];
	for (size_t i = 0; i < _count; i++)
		container[i] = copy.container[i]->Clone();
}

void Row::FreeMemberData()
{
	for (size_t i = 0; i < _count; i++)
		delete container[i];
	delete[] container;
	container = nullptr;
}

void Row::MoveMemberData(Row&& temporary) noexcept
{
	_capacity = temporary._capacity;
	_count = temporary._count;
	container = temporary.container;
	temporary.container = nullptr;
	temporary._count = 0;
}

void Row::Resize(size_t size)
{
	_capacity = size;
	Cell** newContainer = new Cell* [_capacity];
	for (size_t i = 0; i < _count; i++)
		newContainer[i] = container[i];
	delete[] container;
	container = newContainer;
}

Row::Row()
{
	container = new Cell* [DEFAULT_CAPACITY];
}

Row::Row(size_t capacity)
{
	container = new Cell* [capacity];
}

Row::Row(const Row& copy)
{
	CopyMemberData(copy);
}

Row::Row(Row&& temporary) noexcept
{
	MoveMemberData(std::move(temporary));
}

size_t Row::Size() const
{
	return _count;
}

void Row::FillUpTo(size_t count)
{
	for (size_t i = 0; i < count - _count; i++)
		container[_count + i] = CellFactory::CreateCell(TextCell::EMPTY_VALUE);
}

void Row::AddCell(Cell* cell)
{
	if (_count == _capacity)
		Resize(2 * _capacity);
	container[_count++] = cell;
}

void Row::InsertCellAt(size_t column, Cell* cell)
{
	if (column >= _count)
		throw std::runtime_error("Invalid column");
	if (_count == _capacity)
		Resize(_capacity * 2);

	for (int i = _count; i > column; i--)
		container[i] = container[i - 1];
	_count++;
	container[column] = cell;
}

Row& Row::operator=(const Row& row)
{
	if (this != &row)
	{
		FreeMemberData();
		CopyMemberData(row);
	}
	return *this;
}

Row& Row::operator=(Row&& row) noexcept
{
	if (this != &row)
	{
		FreeMemberData();
		MoveMemberData(std::move(row));
	}
	return *this;
}

Vector<UniquePtr<Cell>> Row::Collection() const
{
	Vector<UniquePtr<Cell>> vector;
	for (size_t i = 0; i < _count; i++)
		vector.PushBack(std::move(UniquePtr<Cell>(container[i]->Clone())));
	return vector;
}

const Cell* Row::operator[](unsigned index) const
{
	return container[index];
}

Cell*& Row::operator[](unsigned index)
{
	return container[index];
}

bool Row::IsEmpty() const
{
	return _count == 0;
}

Row::~Row()
{
	FreeMemberData();
}
