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

void String::SetLength(size_t length)
{
	if (IsSmallString())
		if (length < SMALL_STRING_MAX_SIZE)
		{
			LengthByte() = SMALL_STRING_MAX_SIZE - length;
			return;
		}
		else
		{
			char* dynamicData = new char[length];
			size_t len = Length();
			for (size_t i = 0; i < len; i++)
				dynamicData[i] = operator[](i);
			_data = dynamicData;
			_length = length;
			_capacity = length + 1;
			return;
		}
	

	if (length < _capacity)
		_length = length;
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

String::StringView String::SubStringView(unsigned startIndex, size_t length) const
{
	size_t len = Length();
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");
	StringView view;	
	view.data = C_Str() + startIndex;
	view.length =  (startIndex + length < len) ?  length : len - startIndex;
	return view;
}

String::StringView String::SubStringView(unsigned startIndex) const
{
	size_t len = Length();
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");
	StringView view;
	view.data = C_Str() + startIndex;
	view.length = len - startIndex;
	return view;
}

String String::Substring(unsigned startIndex, size_t length) const
{
	size_t len = Length();
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");

	if (length == 0)
		return String();

	String result(length + 1);
	result.SetLength(length);
	for (size_t i = startIndex; i < len && i < startIndex + length; i++)
		result[i - startIndex] = operator[](i);
	result[length] = '\0';
	return result;
}

String String::Substring(unsigned startIndex) const
{
	size_t len = Length(), resultLen = len - startIndex;
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");

	String result(resultLen + 1);
	result.SetLength(resultLen);
	for (size_t i = startIndex; i < len; i++)
		result[i - startIndex] = operator[](i);
	result[resultLen] = '\0';
	return result;
}

const String String::SubstringConst(unsigned startIndex, size_t length) const
{
	return Substring(startIndex, length);
}

const String String::SubstringConst(unsigned startIndex) const
{
	return Substring(startIndex);
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

	for (size_t i = thisLen; i <= resultCapacity; i++)
		result[i] = rhs[i - thisLen];

	delete[] _data;
	_data = result;
	_length = _capacity - 1;

	return *this;
}

String& String::operator+=(char rhs)
{
	size_t len = Length();
	size_t resultCapacity = len + 2;

	if (IsSmallString() && resultCapacity <= SMALL_STRING_MAX_SIZE)
	{
		SetLength(len + 1);
		(*this)[len] = rhs;
		return *this;
	}

	if (!IsSmallString() && resultCapacity <= _capacity)
	{
		_data[len] = rhs;
		_length = resultCapacity - 1;
		return *this;
	}

	_capacity = resultCapacity;
	char* result = new char[_capacity];

	for (size_t i = 0; i < len; i++)
		result[i] = (*this)[i];
	result[len] = rhs;
	delete[] _data;
	_data = result;
	_length = _capacity - 1;
	return *this;
}

char String::operator[](unsigned index) const 
{
	if (index > Length())
		throw std::runtime_error("Index was outside the bounds of the collection");

	if(!IsSmallString())
		return _data[index];
	return CharAt(index);
}

char& String::operator[](unsigned index)
{
	if (index > Length())
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

int String::IndexOf(char symbol, unsigned startIndex) const
{
	int index = -1;
	size_t len = Length();
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");
	for (int i = startIndex; i < len; i++)
		if (operator[](i) == symbol)
			return i;
	return index;
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

int String::LastIndexOf(char symbol, unsigned startIndex) const
{
	int index = -1;
	size_t len = Length();
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");
	for (int i = startIndex; i >= 0; i--)
		if (operator[](i) == symbol)
			return i;
	return index;
}

int String::LastIndexOf(char symbol) const
{
	int index = -1;
	size_t len = Length();
	for (int i = len - 1; i >= 0; i--)
		if (operator[](i) == symbol)
			return i;
	return index;
}

void String::Trim()
{
	size_t len = Length();
	unsigned startIndex = 0, endIndex = len - 1;
	for (unsigned i = 0; i < len; i++)
		if (operator[](i) != ' ')
		{
			startIndex = i;
			break;
		}

	if (startIndex != 0)
	{
		for (size_t i = startIndex; i < len; i++)
			operator[](i - startIndex) = operator[](i);
		len -= startIndex;
		operator[](len) = '\0';
	}

	for (int i = len - 1; i >= 0; i--)
		if (operator[](i) != ' ')
		{
			endIndex = i;
			break;
		}

	if (endIndex < len - 1)
	{
		len = endIndex + 1;
		operator[](len) = '\0';
	}

	SetLength(len);
}

String String::Trim() const
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

	if (startIndex == 0 && endIndex == len - 1)
		return *this;

	size_t resultLen = endIndex + 1 - startIndex;
	String result(resultLen + 1);
	result.SetLength(resultLen);
	for (unsigned i = startIndex; i <= endIndex; i++)
		result[i - startIndex] = operator[](i);
	result[resultLen] = '\0';
	return result;
}

Vector<String> String::Split(char delim) const
{
	Vector<String> result;
	size_t len = Length();
	
	int delimIndex = -1;
	for (size_t i = 0; i < len; i++)
	{
		if (operator[](i) == delim)
		{
			result.PushBack(SubstringConst(delimIndex + 1, i - delimIndex).Trim());
			delimIndex = i;
		}
	}
	if (delimIndex == -1)
		result.PushBack(*this);

	if (delimIndex < len - 1)
		result.PushBack(SubstringConst(delimIndex + 1).Trim());
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

std::ostream& operator<<(std::ostream& output, const String& string)
{
	return output << string.C_Str();
}

bool operator==(const String& lhs, const String& rhs)
{
	return strcmp(lhs.C_Str(), rhs.C_Str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const String& lhs, const String& rhs)
{
	return strcmp(lhs.C_Str(), rhs.C_Str()) < 0;
}

bool operator>(const String& lhs, const String& rhs)
{
	return strcmp(lhs.C_Str(), rhs.C_Str()) > 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return lhs == rhs || lhs < rhs;
}

bool operator>=(const String& lhs, const String& rhs)
{
	return lhs == rhs || lhs > rhs;
}

bool operator==(const String& lhs, const char* rhs)
{
	return strcmp(lhs.C_Str(), rhs) == 0;
}

bool operator!=(const String& lhs, const char* rhs)
{
	return !(lhs == rhs);
}

bool operator<(const String& lhs, const const char* rhs)
{
	return strcmp(lhs.C_Str(), rhs) < 0;
}

bool operator>(const String& lhs, const char* rhs)
{
	return strcmp(lhs.C_Str(), rhs) > 0;
}

bool operator<=(const String& lhs, const char* rhs)
{
	return lhs == rhs || lhs < rhs;
}

bool operator>=(const String& lhs, const char* rhs)
{
	return lhs == rhs || lhs > rhs;
}