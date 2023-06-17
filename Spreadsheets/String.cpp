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

void String::MoveMemberData(String&& temporary) noexcept
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
	LengthByte() = (SMALL_STRING_MAX_SIZE - 1);
}

String::String(size_t length) : String()
{
	size_t capacity = length + 1;
	if (capacity <= SMALL_STRING_MAX_SIZE)
	{
		LengthByte() = (SMALL_STRING_MAX_SIZE - 1) - length;
		CharAt(length) = '\0';
		return;
	}

	_data = new char[capacity];
	_data[length] = '\0';
	_length = length;
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
		LengthByte() = (SMALL_STRING_MAX_SIZE - 1) - capacity + 1;
		for (size_t i = 0; i < capacity; i++)
			CharAt(i) = data[i];
		return;
	}
	
	_data = new char[capacity];
	strcpy(_data, data);
	_length = capacity - 1;
	_capacity = capacity;
}

String::String(const Vector<char>& collection)
{
	size_t len = collection.Count();
	size_t capacity = len + 1;
	if (capacity <= SMALL_STRING_MAX_SIZE)
	{
		LengthByte() = (SMALL_STRING_MAX_SIZE - 1) - capacity + 1;
		for (size_t i = 0; i < len; i++)
			CharAt(i) = collection[i];
		CharAt(len) = '\0';
		return;
	}

	_data = new char[capacity];
	for (size_t i = 0; i < len; i++)
		_data[i] = collection[i];
	_data[len] = '\0';
	_length = capacity - 1;
	_capacity = capacity;
}

String::String(const String& string)
{
	CopyMemberData(string);
}

String::String(String&& temptorary) noexcept
{
	MoveMemberData(std::move(temptorary));
}


size_t String::Length() const
{
	if(IsSmallString())
		return (SMALL_STRING_MAX_SIZE - 1) - LengthByte();
	return _length;
}

size_t String::Capacity() const
{
	if (IsSmallString())
		return SMALL_STRING_MAX_SIZE;
	return _capacity;
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

	String result(length);
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

	String result(resultLen);
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

String& String::operator=(String&& temporary) noexcept
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

	if(IsSmallString() && resultCapacity <= SMALL_STRING_MAX_SIZE )
	{
		LengthByte() = SMALL_STRING_MAX_SIZE - resultCapacity;
		for (size_t i = 0; i <= thatLen; i++)
			operator[](thisLen + i) = rhs[i];
		return *this;
	}

	if (!IsSmallString() && resultCapacity <= _capacity)
	{

		_length = resultCapacity - 1;
		for (size_t i = 0; i <= thatLen; i++)
			operator[](thisLen + i) = rhs[i];
		return *this;
	}

	
	char* result = new char[resultCapacity];

	for (size_t i = 0; i < thisLen; i++)
		result[i] = operator[](i);

	for (size_t i = thisLen; i < resultCapacity; i++)
		result[i] = rhs[i - thisLen];

	if (!IsSmallString())
		delete[] _data;
	_data = result;
	_length = resultCapacity - 1;
	_capacity = resultCapacity;

	return *this;
}

String& String::operator+=(char rhs)
{
	size_t len = Length();
	size_t resultCapacity = len + 2;

	if (IsSmallString() && resultCapacity <= SMALL_STRING_MAX_SIZE ||
	   !IsSmallString() && resultCapacity <= _capacity)
	{
		operator[](len) = rhs;	
		return *this;
	}

	_capacity = resultCapacity;
	char* result = new char[_capacity];

	for (size_t i = 0; i < len; i++)
		result[i] = operator[](i);
	result[len] = rhs;
	delete[] _data;
	_data = result;
	_length = _capacity - 1;
	return *this;
}

char String::operator[](unsigned index) const 
{
	if(!IsSmallString())
		return _data[index];
	return CharAt(index);
}

char& String::operator[](unsigned index)
{
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

size_t String::CountChar(char symbol) const
{
	size_t count = 0, length = Length();
	for (size_t i = 0; i < length; i++)
		if (operator[](i) == symbol)
			count++;
	return count;
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
	for (unsigned i = 0; i < len; i++, startIndex++)
		if (operator[](i) != ' ')
			break;

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

}

String String::Trim(const String& string)
{
	size_t length = string.Length();
	unsigned startIndex = 0, endIndex = length - 1;

	for (size_t i = 0; i < length; i++)
		if (string[i] != ' ')
		{
			startIndex = i;
			break;
		}

	for (long i = length - 1; i >= 0; i--)
		if (string[i] != ' ')
		{
			endIndex = i;
			break;
		}

	if (startIndex == 0 && endIndex == length - 1)
		return string;

	size_t resultLen = endIndex + 1 - startIndex;
	String result(resultLen + 1);
	for (unsigned i = startIndex; i <= endIndex; i++)
		result[i - startIndex] = string[i];
	result[resultLen] = '\0';
	return result;
}

Vector<String> String::Split(char delim) const
{
	Vector<String> result;
	Vector<char> string;
	size_t len = Length();
	
	int delimIndex = -1;
	bool collecting = true;
	for (size_t i = 0; i < len; i++)
	{
		char currentChar = operator[](i);
		if (currentChar == delim)
		{
			delimIndex = i;
			if (collecting)
			{
				result.PushBack(string);
				string = std::move(Vector<char>());
				collecting = false;
			}		
		}
		if (currentChar != delim)
			collecting = true;
		if (collecting)
			string.PushBack(currentChar);
	}
	if (delimIndex == -1)
		result.PushBack(*this);

	if (delimIndex < len - 1)
		result.PushBack(String::Trim(SubstringConst(delimIndex + 1)));
	return result;
}


bool IsDigit(char symbol)
{
	if (symbol >= '0' && symbol <= '9')
		return true;
	return false;
}

size_t CharToDigit(char symbol)
{
	return symbol - '0';
}

bool IsAllowedInInteger(char symbol, unsigned index)
{
	if (IsDigit(symbol))
		return true;
	if (symbol == '+' || symbol == '-')
		return index == 0;
	return false;
}

bool String::IsInteger() const
{
	size_t length = Length();
	for (size_t i = 0; i < length; i++)
	{
		char current = operator[](i);
		if (!IsAllowedInInteger(current, i))
			return false;
	}
	return true;
}

size_t String::IntegerParse() const
{
	size_t result = 0, length = Length();
	char  current = operator[](0);
	if (IsDigit(current))
		result += CharToDigit(current);
	for (size_t i = 1; i < length; i++)
		result += CharToDigit(current);
	return result;
}

bool IsAllowedInDecimal(char symbol, size_t& decimalsCounter, unsigned index)
{
	if (IsDigit(symbol))
		return true;
	if (symbol == '+' || symbol == '-')
		return index == 0;
	if (symbol == '.' || symbol == ',')
		return decimalsCounter++ <= 1;
	return false;
}

bool String::IsDecimal() const
{
	size_t length = Length(), decimalsCounter = 0;
	for (size_t i = 0; i < length; i++)
	{
		char current = operator[](i);
		if (!IsAllowedInDecimal(current, decimalsCounter, i))
			return false;
	}
	return true;
}

size_t String::DecimalParse() const
{
	return size_t();
}

size_t GetLength(size_t number)
{
	size_t length = 0;
	while (number != 0)
	{
		number /= 10;
		length++;
	}
	return number == 0 ? 1 : length;
}

char DigitToChar(byte number)
{
	if(number > 9)
		throw std::runtime_error("Invalid digit");
	return number + '0';
}

String String::NumericString(size_t number)
{
	size_t length = GetLength(number);
	String result(length + 1);

	for (int i = length - 1; i >= 0; i--, number /= 10)
		result[i] = DigitToChar(number % 10);

	result[length] = '\0';
	return result;
}

String String::NumericString(int number)
{
	return String();
}

String String::NumericString(double number)
{
	return String();
}

String operator+(const String& lhs, const String& rhs)
{
	size_t thisLen = lhs.Length(), thatLen = rhs.Length(), totalLen = thisLen + thatLen;
	String result(totalLen);
	for (size_t i = 0; i < thisLen; i++)
		result[i] = lhs[i];
	for (size_t i = thisLen; i <= totalLen; i++)
		result[i] = rhs[i - thisLen];
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

std::istream& ReadLine(std::istream& input, String& string, char delim)
{
	char buffer[1024];
	input.getline(buffer, 1024, delim);
	string = buffer;
	return input;
}
