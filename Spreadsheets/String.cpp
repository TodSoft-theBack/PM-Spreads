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
		throw std::runtime_error("Index was outside the string");

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
		throw std::runtime_error("Index was outside the string");

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
		LengthByte() = SMALL_STRING_MAX_SIZE - 1;
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

String::String(const StringView& string)
{
	if (string.length == 0)
	{
		LengthByte() = SMALL_STRING_MAX_SIZE - 1;
		return;
	}
	size_t capacity = string.length + 1;
	if (capacity <= SMALL_STRING_MAX_SIZE)
	{
		LengthByte() = (SMALL_STRING_MAX_SIZE - 1) - capacity + 1;
		for (size_t i = 0; i < string.length; i++)
			CharAt(i) = string[i];
		CharAt(string.length) = '\0';
		return;
	}

	_data = new char[capacity];
	for (size_t i = 0; i < string.length; i++)
		_data[i] = string[i];
	_data[string.length] = '\0';
	_length = capacity - 1;
	_capacity = capacity;
}

String::String(const Vector<char>& collection)
{
	size_t len = collection.Count();
	size_t capacity = len + 1;
	if (capacity <= SMALL_STRING_MAX_SIZE)
	{
		LengthByte() = (SMALL_STRING_MAX_SIZE - 1) - len;
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

String::StringView String::SubstringView(unsigned startIndex, size_t length) const
{
	size_t len = Length();
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");
	StringView view;	
	view.data = C_Str() + startIndex;
	view.length =  (startIndex + length < len) ?  length : len - startIndex;
	return view;
}

String::StringView String::SubstringView(unsigned startIndex) const
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
		LengthByte() = (SMALL_STRING_MAX_SIZE - 1) - len - 1;
		operator[](len) = rhs;
		operator[](len + 1) = '\0';
		return *this;
	}

	_capacity = resultCapacity;
	char* result = new char[_capacity];

	for (size_t i = 0; i < len; i++)
		result[i] = operator[](i);
	result[len] = rhs;
	result[len+1] = '\0';
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

char String::First() const
{
	return operator[](0);
}

char String::Last() const
{
	return operator[](Length() - 1);
}

String::operator const char* () const
{
	return C_Str();
}

String::StringView String::GetStringView() const
{
	StringView view;
	view.data = C_Str();
	view.length = Length();
	return view;
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
	if (length == 0)
		return string;
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

	if (startIndex == endIndex)
		return string[startIndex] == ' ' ? String() : string;

	if (startIndex == 0 && endIndex == length - 1)
		return string;

	size_t resultLen = endIndex + 1 - startIndex;
	String result(resultLen + 1);
	for (unsigned i = startIndex; i <= endIndex; i++)
		result[i - startIndex] = string[i];
	result[resultLen] = '\0';
	return result;
}

String String::Trim(const StringView& string)
{
	size_t length = string.length;
	if (length == 0)
		return String();
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
		return String(string);

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
	for (size_t i = 0; i < len; i++)
	{
		char currentChar = operator[](i);
		if (currentChar == delim)
		{
			delimIndex = i;
			result.PushBack(String::Trim(string));
			string = std::move(Vector<char>());
			continue;
		}
		string.PushBack(currentChar);
	}
	if (delimIndex == -1)
	{
		result.PushBack(*this);
		return result;
	}
	if (!string.IsEmpty())
		result.PushBack(String::Trim(string));
	return result;
}

bool String::IsEmpty() const
{
	return Length() == 0;
}

String::NumericType String::CheckType() const
{
	NumericType type = NumericType::Integer;
	size_t length = Length();
	bool hasDecimals = false;
	for (size_t i = 0; i < length; i++)
	{
		char current = operator[](i);
		if (type == NumericType::Integer && !IsAllowedInInteger(current, i))
			type = NumericType::Decimal;

		if (type == NumericType::Decimal && !IsAllowedInDecimal(current, hasDecimals, i))
			type = NumericType::NaN;

		if (type == NumericType::NaN)
			break;
	}
	return type;
}


bool String::IsDigit(char symbol)
{
	if (symbol >= '0' && symbol <= '9')
		return true;
	return false;
}

byte String::CharToDigit(char symbol)
{
	return symbol - '0';
}

bool String::IsAllowedInInteger(char symbol, unsigned index)
{
	if (String::IsDigit(symbol))
		return true;
	if (symbol == '+' || symbol == '-')
		return index == 0;
	return false;
}

bool String::IsInteger() const
{
	size_t length = Length();
	if (length == 0)
		return false;
	for (size_t i = 0; i < length; i++)
	{
		char current = operator[](i);
		if (!IsAllowedInInteger(current, i))
			return false;
	}
	return true;
}

int String::IntegerParse() const
{
	int result = 0;
	size_t length = Length();
	char  current = operator[](0);
	bool isNegative = false;
	if (IsDigit(current))
		result += CharToDigit(current);
	else if (current == '-')
		isNegative = true;
	else if (current != '+')
		throw std::runtime_error("Cannot parse string to integer!!!");

	for (size_t i = 1; i < length; i++)
	{
		current = operator[](i);
		if (!IsDigit(current))
			throw std::runtime_error("Cannot parse string to integer!!!");
		(result *= 10) += CharToDigit(operator[](i));
	}
	if (isNegative)
		return -result;
	return result;
}

bool String::IsAllowedInDecimal(char symbol, bool& hasDecimalsAlready, unsigned index)
{
	if (String::IsDigit(symbol))
		return true;
	if (symbol == '+' || symbol == '-')
		return index == 0;
	if (symbol == '.' || symbol == ',')
	{
		if (hasDecimalsAlready)
			return false;
		hasDecimalsAlready = true;
		return true;
	}
	return false;
}

bool String::IsDecimal() const
{
	size_t length = Length();
	if (length == 0)
		return false;
	bool hasDecimalsAlready = false;
	for (size_t i = 0; i < length; i++)
	{
		char current = operator[](i);
		if (!IsAllowedInDecimal(current, hasDecimalsAlready, i))
			return false;
	}
	return true;
}

double String::DecimalParse() const
{
	double result = 0;
	size_t length = Length();
	bool hasDecimalAlready = false;
	unsigned decimalIndex = length;
	char  current = operator[](0);
	bool isNegative = false;
	if (String::IsDigit(current))
		result += CharToDigit(current);
	else if (current == '-')
		isNegative = true;
	else if (current != '+')
		throw std::runtime_error("Cannot parse string to decimal!!!");

	for (size_t i = 1; i < length; i++)
	{
		current = operator[](i);
		if (current == '.' || current == ',')
		{
			if (hasDecimalAlready)
				throw std::runtime_error("Cannot parse string to decimal!!!");
			hasDecimalAlready = true;
			decimalIndex = i;
			continue;
		}
		(result *= 10) += CharToDigit(operator[](i));
	}

	for (size_t i = decimalIndex + 1; i < length; i++)
		result /= 10.0;

	if (isNegative)
		return -result;
	return result;
}

size_t String::GetLength(size_t number)
{
	size_t length = 0;
	while (number != 0)
	{
		number /= 10;
		length++;
	}
	return number == 0 ? 1 : length;
}

size_t String::GetLength(int number)
{
	if (number == 0)
		return 1;
	size_t length = 0;
	if (number < 0)
		length = 1;
	do
	{
		number /= 10;
		length++;
	} while (number != 0);
}

char String::DigitToChar(byte number)
{
	if(number > 9)
		throw std::runtime_error("Invalid digit");
	return number + '0';
}

String String::NumericString(size_t number)
{
	size_t length = String::GetLength(number);
	String result(length);

	for (int i = length - 1; i >= 0; i--, number /= 10)
		result[i] = DigitToChar((byte)(number % 10));

	result[length] = '\0';
	return result;
}

String String::NumericString(int number)
{
	size_t length = String::GetLength(number);
	size_t naturalNumber = number < 0 ? -number : number;

	String result(length);

	for (int i = length - 1; i > 0; i--, naturalNumber /= 10)
		result[i] = DigitToChar(naturalNumber % 10);

	if (number < 0)
		result[0] = '-';
	else
		result[0] = DigitToChar(naturalNumber % 10);

	result[length] = '\0';
	return result;
}

String String::NumericString(double number)
{
	return NumericString(number, DEFAULT_PRECISION);
}

String String::NumericString(double number, size_t precision)
{
	int wholePart = (int)number;
	size_t length = GetLength(wholePart), resultLength = length + 1 + precision + (number < 0);
	size_t naturalNumber = wholePart < 0 ? -wholePart : wholePart;
	Vector<char> result(resultLength);

	if (number < 0)
		result.PushBack('-');

	for (int i = length - 1; i >= 0; i--, naturalNumber /= 10)
		result.PushBack(DigitToChar(naturalNumber % 10));

	result.PushBack('.');

	double decimalPart = number - wholePart, 
		absDecimalPart = decimalPart < 0 ? -decimalPart : decimalPart;
	for (size_t i = 0; i < precision; i++)
	{
		uint8_t digit = (uint8_t)(absDecimalPart *= 10);
		absDecimalPart -= digit;
		result.PushBack(DigitToChar(digit));
	}
	return result;
}

String String::GetFromString(const char* value)
{
	size_t length = strlen(value);
	if (value[0] != '\"' || value[length - 1] != '\"')
		throw std::runtime_error("Invalid string!!!");
	Vector<char> result(length - 2);
	for (size_t i = 1; i < length - 1; i++)
	{
		if(value[i] != '\\')
			result.PushBack(value[i]);
	}
	return result;
}

bool String::IsEscapeChar(char symbol)
{
	return symbol == '\"' || symbol == '\'' || symbol == '\\';
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
	return strcmp(lhs, rhs) == 0;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const String& lhs, const String& rhs)
{
	return strcmp(lhs, rhs) < 0;
}

bool operator>(const String& lhs, const String& rhs)
{
	return strcmp(lhs, rhs) > 0;
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
	return strcmp(lhs, rhs) == 0;
}

bool operator!=(const String& lhs, const char* rhs)
{
	return !(lhs == rhs);
}

bool operator<(const String& lhs, const const char* rhs)
{
	return strcmp(lhs, rhs) < 0;
}

bool operator>(const String& lhs, const char* rhs)
{
	return strcmp(lhs, rhs) > 0;
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

const char& String::StringView::operator[](unsigned index) const
{
	return data[index];
}

String::StringView String::StringView::SubstringView(unsigned startIndex) const
{
	if (startIndex >= length)
		throw std::runtime_error("Invalid index");
	StringView view;
	view.data = data + startIndex;
	view.length = length - startIndex;
	return view;
}

String::StringView String::StringView::SubstringView(unsigned startIndex, unsigned length) const
{
	size_t len = this->length;
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");
	StringView view;
	view.data = data + startIndex;
	view.length = (startIndex + length < len) ? length : len - startIndex;
	return view;
}