#include "Row.h"


Row Row::ParseLine(const String& line)
{
	if (line.Length() == 0)
		return Row();
	Vector<String> values = line.Split(',');
	size_t count = values.Count();
	Row result(count);
	for (size_t i = 0; i < count; i++)
		result.AddCell(CellFactory::CreateCell(String::Trim(values[i]).C_Str()));
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
}

void Row::Resize(size_t size)
{
	_capacity = size;
	Cell** newContainer = new Cell* [_capacity];
	for (size_t i = 0; i < _count; i++)
	{
		newContainer[i] = container[i]->Clone();
		delete container[i];
	}
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

void Row::AddCell(Cell* cell)
{
	if (_count == _capacity)
		Resize(2 * _capacity);
	container[_count++] = cell;
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

Row::~Row()
{
	FreeMemberData();
}
