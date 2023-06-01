#pragma warning(disable: 4996)
#include "String.h"

void String::CopyMemberData(const String& copy)
{
	_length = copy._length;
	_capacity = copy._capacity;
	if(copy.IsSmallString())
		_data = copy._data;
	else
	{
		_data = new char[_capacity];
		strcpy(_data, copy._data);
	}
}

void String::MoveMemberData(String&& temporary)
{
	if(temporary.IsSmallString())
	{
		CopyMemberData(temporary);
		return;
	}

	_length = temporary._length;
	_data = temporary._data;
	temporary._data = nullptr;
	_capacity = temporary._capacity;
}

void String::FreeMemberData()
{
	if(IsSmallString())
		return;
	delete[] _data;
	_data = nullptr;
}

bool String::IsSmallString() const
{
	return LengthByte() != 0  ? true : LastByteOf(_length) != 0;
}

byte String::LengthByte() const
{
	return LastByteOf(_capacity);
}

byte& String::LengthByte()
{
	return LastByteOf(_capacity);
}

byte String::LastByteOf(size_t variable) const
{
	return ((byte*)&variable)[sizeof(variable) - 1];
}

byte& String::LastByteOf(size_t& variable)
{
	return ((byte*)&variable)[sizeof(variable) - 1];
}

char String::CharAt(unsigned index) const
{
	if (index >= SMALL_STRING_MAX_SIZE)
		throw std::runtime_error("Index was outside the bounds of the collection");

	if(index < sizeof(_data))
		return ((char*)(&_data))[index]; 
	else if (index < sizeof(_data) + sizeof(_length))
		return ((char*)(&_length))[index - sizeof(_data)];
	else
		return ((char*)(&_capacity))[index - sizeof(_data) - sizeof(_length)];
}
char& String::CharAt(unsigned index)
{
	if (index >= SMALL_STRING_MAX_SIZE)
		throw std::runtime_error("Index was outside the bounds of the collection");

	if(index < sizeof(_data))
		return ((char*)(&_data))[index]; 
	else if (index < sizeof(_data) + sizeof(_length))
		return ((char*)(&_length))[index - sizeof(_data)];
	else
		return ((char*)(&_capacity))[index - sizeof(_data) - sizeof(_length)];
}

String::String()
{
	LengthByte() = SMALL_STRING_MAX_SIZE;
}

String::String(size_t capacity) : String()
{
	if (capacity <= SMALL_STRING_MAX_SIZE)
		return;
	_data = new char[capacity];
	_data[0] = '\0';
	_length = 0;
	_capacity = capacity;
}

String::String(const char* data)
{
	if(data == nullptr)
	{
		LengthByte() = SMALL_STRING_MAX_SIZE;
		return;
	}
	size_t capacity = strlen(data) + 1;
	if(capacity <= SMALL_STRING_MAX_SIZE)
	{
		_capacity = 0;
		LengthByte() = SMALL_STRING_MAX_SIZE - capacity;
		for (size_t i = 0; i < capacity; i++)
			CharAt(i) = data[i];
		return;
	}
	
	_data = new char[capacity];
	strcpy(_data, data);
	_length = capacity - 1;
	_capacity = capacity;
}

String::String(std::istream& input)
{
	char buffer[1024] = {'\0'};
	input.getline(buffer, 1024);

	size_t len = strlen(buffer);

	if (len == 0)
	{
		LengthByte() = SMALL_STRING_MAX_SIZE;
		return;
	}
	size_t capacity = len + 1;
	if (capacity <= SMALL_STRING_MAX_SIZE)
	{
		_capacity = 0;
		LengthByte() = SMALL_STRING_MAX_SIZE - capacity;
		for (size_t i = 0; i < capacity; i++)
			CharAt(i) = buffer[i];
		return;
	}

	_data = new char[capacity];
	strcpy(_data, buffer);
	_length = capacity - 1;
	_capacity = capacity;
	
}

String::String(const String& string)
{
	CopyMemberData(string);
}

String::String(String&& temptorary)
{
	MoveMemberData(std::move(temptorary));
}


size_t String::Length() const
{
	if(IsSmallString())
		return SMALL_STRING_MAX_SIZE - LengthByte();
	return _length;
}

String::StringView String::SubStringView(unsigned startIndex, size_t length)
{
	size_t len = Length();
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");
	StringView view;	
	view.data = C_Str() + startIndex;
	view.length =  (startIndex + length < len) ?  length : len - startIndex;
	return view;
}

String String::Substring(unsigned startIndex, size_t length)
{
	size_t len = Length();
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");
	if (length == 0)
		return String();

	String result(length + 1);
	for (size_t i = startIndex; i < len && i < startIndex + length; i++)
		result[i - startIndex] = operator[](i);
	result[startIndex + length] = '\0';
	return result;
}

String& String::operator=(const String& rhs)
{
	if (this != &rhs)
	{
		FreeMemberData();
        CopyMemberData(rhs);
	}
	return *this;
}

String& String::operator=(String&& temporary)
{
	if (this != &temporary)
	{
		FreeMemberData();
        MoveMemberData(std::move(temporary));
	}
	return *this;
}

String& String::operator+=(const String& rhs)
{
	size_t thisLen = Length(), thatLen = rhs.Length();
	size_t resultCapacity = thisLen + thatLen + 1;

	if(IsSmallString() && resultCapacity <= SMALL_STRING_MAX_SIZE)
	{
		for (size_t i = 0; i <= thatLen; i++)
			(*this)[thisLen + i] =  rhs[i];
		return *this;
	}

	if (!IsSmallString() && resultCapacity <= _capacity)
	{
		for (size_t i = 0; i <= thatLen; i++)
			_data[thisLen + i] = rhs[i];
		_length = resultCapacity - 1;
		return *this;
	}

	_capacity = resultCapacity;
	char* result = new char[_capacity];

	for (size_t i = 0; i < thisLen; i++)
		result[i] = (*this)[i];

	for (size_t i = thisLen; i <= thisLen + thatLen + 1; i++)
		result[i] = rhs[i - thisLen];

	delete[] _data;
	_data = result;
	_length = _capacity - 1;

	return *this;
}

char String::operator[](unsigned index) const 
{
	if (index >= Length())
		throw std::runtime_error("Index was outside the bounds of the collection");

	if(!IsSmallString())
		return _data[index];
	return CharAt(index);
}

char& String::operator[](unsigned index)
{
	if (index >= Length())
		throw std::runtime_error("Index was outside the bounds of the collection");

	if (!IsSmallString())
		return _data[index];
	return CharAt(index);
}

const char* String::C_Str() const
{
	if (!IsSmallString())
		return this->_data;
	return (char*)this;
}

int String::IndexOf(char symbol) const
{
	int index = -1;
	size_t len = Length();
	for (int i = 0; i < len; i++)
		if (operator[](i) == symbol)
			return i;
	return index;
}

void String::Trim()
{
	size_t len = Length();
	unsigned startIndex = 0, endIndex = len - 1;
	for (size_t i = 0; i < len; i++)
		if (operator[](i) != ' ')
		{
			startIndex = i;
			break;
		}

	for (long i = len - 1; i >= 0; i--)
		if (operator[](i) != ' ')
		{
			endIndex = i;
			break;
		}
}

String String::Trim() const
{
	String result;
	if (!IsSmallString())
		result = String(_capacity);
	size_t len = Length();
	unsigned startIndex = 0, endIndex = len - 1;
	for (size_t i = 0; i < len; i++)
		if (operator[](i) != ' ')
		{
			startIndex = i;
			break;
		}
	for (long i = len - 1; i >= 0; i--)
		if (operator[](i) != ' ')
		{
			endIndex = i;
			break;
		}

	for (unsigned i = startIndex; i < endIndex; i++)
		result[i - startIndex] = operator[](i);
	return result;
}

Vector<String> String::Split(char delim)
{
	Vector<String> result;
	size_t len = Length();
	
	int delimIndex = -1;
	for (size_t i = 0; i < len; i++)
	{
		if (operator[](i) == delim)
		{
			if (delimIndex == -1)
				delimIndex = 0;
			result.PushBack(Substring(delimIndex, i - delimIndex));
			delimIndex = i;
		}
	}
	return result;
}

String operator+(const String& lhs, const String& rhs)
{
	size_t thisLen = lhs.Length(), thatLen = rhs.Length();
	String result(thisLen + thatLen + 1);
	result += lhs;
	result += rhs;
	return result;
}

std::ostream& operator<<(std::ostream& output, const String& string)
{
    return output << string.C_Str();
}

std::istream& operator>>(std::istream& input, String& string)
{
	char buffer[1024];
	input >> buffer;
	string = buffer;	
    return input;
}

String::~String()
{
	FreeMemberData();
}