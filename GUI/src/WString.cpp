#pragma warning(disable: 4996)
#include "WString.h"

void WString::CopyMemberData(const WString& copy)
{
	_length = copy._length;
	_capacity = copy._capacity;
	if(copy.IsSmallString())
		_data = copy._data;
	else
	{
		_data = new wchar_t[_capacity];
		wcscpy(_data, copy._data);
	}
}

void WString::MoveMemberData(WString&& temporary) noexcept
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

void WString::FreeMemberData()
{
	if(IsSmallString())
		return;
	delete[] _data;
	_data = nullptr;
}

bool WString::IsSmallString() const
{
	return LengthByte() != 0  ? true : LastByteOf(_length) != 0;
}

byte WString::LengthByte() const
{
	return LastByteOf(_capacity);
}

byte& WString::LengthByte()
{
	return LastByteOf(_capacity);
}

byte WString::LastByteOf(size_t variable) const
{
	return ((byte*)&variable)[sizeof(variable) - 1];
}

byte& WString::LastByteOf(size_t& variable)
{
	return ((byte*)&variable)[sizeof(variable) - 1];
}

wchar_t WString::wchar_tAt(unsigned index) const
{
	if (index >= SMALL_STRING_MAX_SIZE)
		throw std::runtime_error("Index was outside the WString");

	if(index < sizeof(_data))
		return ((wchar_t*)(&_data))[index]; 
	else if (index < sizeof(_data) + sizeof(_length))
		return ((wchar_t*)(&_length))[index - sizeof(_data)];
	else
		return ((wchar_t*)(&_capacity))[index - sizeof(_data) - sizeof(_length)];
}
wchar_t& WString::wchar_tAt(unsigned index)
{
	if (index >= SMALL_STRING_MAX_SIZE)
		throw std::runtime_error("Index was outside the WString");

	if(index < sizeof(_data))
		return ((wchar_t*)(&_data))[index]; 
	else if (index < sizeof(_data) + sizeof(_length))
		return ((wchar_t*)(&_length))[index - sizeof(_data)];
	else
		return ((wchar_t*)(&_capacity))[index - sizeof(_data) - sizeof(_length)];
}

WString::WString()
{
	LengthByte() = (SMALL_STRING_MAX_SIZE - 1);
}

WString::WString(size_t length) : WString()
{
	size_t capacity = length + 1;
	if (capacity <= SMALL_STRING_MAX_SIZE)
	{
		LengthByte() = (SMALL_STRING_MAX_SIZE - 1) - length;
		wchar_tAt(length) = '\0';
		return;
	}

	_data = new wchar_t[capacity];
	_data[length] = '\0';
	_length = length;
	_capacity = capacity;
}

WString::WString(const wchar_t* data)
{
	if(data == nullptr)
	{
		LengthByte() = SMALL_STRING_MAX_SIZE - 1;
		return;
	}
	size_t capacity = wcslen(data) + 1;
	if(capacity <= SMALL_STRING_MAX_SIZE)
	{
		LengthByte() = (SMALL_STRING_MAX_SIZE - 1) - capacity + 1;
		for (size_t i = 0; i < capacity; i++)
			wchar_tAt(i) = data[i];
		return;
	}
	
	_data = new wchar_t[capacity];
	wcscpy(_data, data);
	_length = capacity - 1;
	_capacity = capacity;
}

WString::WString(const WStringView& WString)
{
	if (WString.length == 0)
	{
		LengthByte() = SMALL_STRING_MAX_SIZE - 1;
		return;
	}
	size_t capacity = WString.length + 1;
	if (capacity <= SMALL_STRING_MAX_SIZE)
	{
		LengthByte() = (SMALL_STRING_MAX_SIZE - 1) - capacity + 1;
		for (size_t i = 0; i < WString.length; i++)
			wchar_tAt(i) = WString[i];
		wchar_tAt(WString.length) = '\0';
		return;
	}

	_data = new wchar_t[capacity];
	for (size_t i = 0; i < WString.length; i++)
		_data[i] = WString[i];
	_data[WString.length] = '\0';
	_length = capacity - 1;
	_capacity = capacity;
}


WString::WString(const WString& WString)
{
	CopyMemberData(WString);
}

WString::WString(WString&& temptorary) noexcept
{
	MoveMemberData(std::move(temptorary));
}


size_t WString::Length() const
{
	if(IsSmallString())
		return (SMALL_STRING_MAX_SIZE - 1) - LengthByte();
	return _length;
}

size_t WString::Capacity() const
{
	if (IsSmallString())
		return SMALL_STRING_MAX_SIZE;
	return _capacity;
}

WString::WStringView WString::SubstringView(unsigned startIndex, size_t length) const
{
	size_t len = Length();
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");
	WStringView view;	
	view.data = C_Str() + startIndex;
	view.length =  (startIndex + length < len) ?  length : len - startIndex;
	return view;
}

WString::WStringView WString::SubstringView(unsigned startIndex) const
{
	size_t len = Length();
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");
	WStringView view;
	view.data = C_Str() + startIndex;
	view.length = len - startIndex;
	return view;
}

WString WString::Substring(unsigned startIndex, size_t length) const
{
	size_t len = Length();
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");

	if (length == 0)
		return WString();

	WString result(length);
	for (size_t i = startIndex; i < len && i < startIndex + length; i++)
		result[i - startIndex] = operator[](i);
	result[length] = '\0';
	return result;
}

WString WString::Substring(unsigned startIndex) const
{
	size_t len = Length(), resultLen = len - startIndex;
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");

	WString result(resultLen);
	for (size_t i = startIndex; i < len; i++)
		result[i - startIndex] = operator[](i);
	result[resultLen] = '\0';
	return result;
}

WString& WString::operator=(const WString& rhs)
{
	if (this != &rhs)
	{
		FreeMemberData();
        CopyMemberData(rhs);
	}
	return *this;
}

WString& WString::operator=(WString&& temporary) noexcept
{
	if (this != &temporary)
	{
		FreeMemberData();
        MoveMemberData(std::move(temporary));
	}
	return *this;
}

WString& WString::operator+=(const WString& rhs)
{
	size_t thisLen = Length(), thatLen = rhs.Length();
	size_t resultCapacity = thisLen + thatLen + 1;

	if(IsSmallString() && resultCapacity <= SMALL_STRING_MAX_SIZE)
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

	
	wchar_t* result = new wchar_t[resultCapacity];

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

WString& WString::operator+=(wchar_t rhs)
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
	wchar_t* result = new wchar_t[_capacity];

	for (size_t i = 0; i < len; i++)
		result[i] = operator[](i);
	result[len] = rhs;
	result[len+1] = '\0';
	delete[] _data;
	_data = result;
	_length = _capacity - 1;
	return *this;
}

wchar_t WString::operator[](unsigned index) const 
{
	if(!IsSmallString())
		return _data[index];
	return wchar_tAt(index);
}

wchar_t& WString::operator[](unsigned index)
{
	if (!IsSmallString())
		return _data[index];
	return wchar_tAt(index);
}

wchar_t WString::First() const
{
	return operator[](0);
}

wchar_t WString::Last() const
{
	return operator[](Length() - 1);
}

WString::operator const wchar_t* () const
{
	return C_Str();
}

WString::WStringView WString::GetStringView() const
{
	WStringView view;
	view.data = C_Str();
	view.length = Length();
	return view;
}

const wchar_t* WString::C_Str() const
{
	if (!IsSmallString())
		return this->_data;
	return (wchar_t*)this;
}

size_t WString::Countwchar_t(wchar_t symbol) const
{
	size_t count = 0, length = Length();
	for (size_t i = 0; i < length; i++)
		if (operator[](i) == symbol)
			count++;
	return count;
}

int WString::IndexOf(wchar_t symbol, unsigned startIndex) const
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

int WString::IndexOf(wchar_t symbol) const
{
	int index = -1;
	size_t len = Length();
	for (int i = 0; i < len; i++)
		if (operator[](i) == symbol)
			return i;
	return index;
}

int WString::LastIndexOf(wchar_t symbol, unsigned startIndex) const
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

int WString::LastIndexOf(wchar_t symbol) const
{
	int index = -1;
	size_t len = Length();
	for (int i = len - 1; i >= 0; i--)
		if (operator[](i) == symbol)
			return i;
	return index;
}

void WString::Trim()
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

WString WString::Trim(const WString& string)
{
	size_t length = string.Length();
	if (length == 0)
		return WString();
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
		return string[startIndex] == ' ' ? WString() : string;

	if (startIndex == 0 && endIndex == length - 1)
		return string;

	size_t resultLen = endIndex + 1 - startIndex;
	WString result(resultLen + 1);
	for (unsigned i = startIndex; i <= endIndex; i++)
		result[i - startIndex] = string[i];
	result[resultLen] = '\0';
	return result;
}

WString WString::Trim(const WStringView& string)
{
	size_t length = string.length;
	if (length == 0)
		return WString();
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
		return WString(string);

	size_t resultLen = endIndex + 1 - startIndex;
	WString result(resultLen + 1);
	for (unsigned i = startIndex; i <= endIndex; i++)
		result[i - startIndex] = string[i];
	result[resultLen] = '\0';
	return result;
}

bool WString::IsEmpty() const
{
	return Length() == 0;
}

WString::NumericType WString::CheckType() const
{
	NumericType type = NumericType::Integer;
	size_t length = Length();
	bool hasDecimals = false;
	for (size_t i = 0; i < length; i++)
	{
		wchar_t current = operator[](i);
		if (type == NumericType::Integer && !IsAllowedInInteger(current, i))
			type = NumericType::Decimal;

		if (type == NumericType::Decimal && !IsAllowedInDecimal(current, hasDecimals, i))
			type = NumericType::NaN;

		if (type == NumericType::NaN)
			break;
	}
	return type;
}


bool WString::IsDigit(wchar_t symbol)
{
	if (symbol >= '0' && symbol <= '9')
		return true;
	return false;
}

byte WString::CharToDigit(wchar_t symbol)
{
	return symbol - '0';
}

bool WString::IsAllowedInInteger(wchar_t symbol, unsigned index)
{
	if (WString::IsDigit(symbol))
		return true;
	if (symbol == '+' || symbol == '-')
		return index == 0;
	return false;
}

bool WString::IsInteger() const
{
	size_t length = Length();
	if (length == 0)
		return false;
	for (size_t i = 0; i < length; i++)
	{
		wchar_t current = operator[](i);
		if (!IsAllowedInInteger(current, i))
			return false;
	}
	return true;
}

int WString::IntegerParse() const
{
	int result = 0;
	size_t length = Length();
	wchar_t  current = operator[](0);
	bool isNegative = false;
	if (IsDigit(current))
		result += CharToDigit(current);
	else if (current == '-')
		isNegative = true;
	else if (current != '+')
		throw std::runtime_error("Cannot parse WString to integer!!!");

	for (size_t i = 1; i < length; i++)
	{
		current = operator[](i);
		if (!IsDigit(current))
			throw std::runtime_error("Cannot parse WString to integer!!!");
		(result *= 10) += CharToDigit(operator[](i));
	}
	if (isNegative)
		return -result;
	return result;
}

bool WString::IsAllowedInDecimal(wchar_t symbol, bool& hasDecimalsAlready, unsigned index)
{
	if (WString::IsDigit(symbol))
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

bool WString::IsDecimal() const
{
	size_t length = Length();
	if (length == 0)
		return false;
	bool hasDecimalsAlready = false;
	for (size_t i = 0; i < length; i++)
	{
		wchar_t current = operator[](i);
		if (!IsAllowedInDecimal(current, hasDecimalsAlready, i))
			return false;
	}
	return true;
}

double WString::DecimalParse() const
{
	double result = 0;
	size_t length = Length();
	bool hasDecimalAlready = false;
	unsigned decimalIndex = length;
	wchar_t  current = operator[](0);
	bool isNegative = false;
	if (WString::IsDigit(current))
		result += CharToDigit(current);
	else if (current == '-')
		isNegative = true;
	else if (current != '+')
		throw std::runtime_error("Cannot parse WString to decimal!!!");

	for (size_t i = 1; i < length; i++)
	{
		current = operator[](i);
		if (current == '.' || current == ',')
		{
			if (hasDecimalAlready)
				throw std::runtime_error("Cannot parse WString to decimal!!!");
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

size_t WString::GetLength(size_t number)
{
	size_t length = 0;
	while (number != 0)
	{
		number /= 10;
		length++;
	}
	return number == 0 ? 1 : length;
}

size_t WString::GetLength(int number)
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

wchar_t WString::DigitToChar(byte number)
{
	if(number > 9)
		throw std::runtime_error("Invalid digit");
	return number + '0';
}

WString WString::NumericString(size_t number)
{
	size_t length = WString::GetLength(number);
	WString result(length);

	for (int i = length - 1; i >= 0; i--, number /= 10)
		result[i] = DigitToChar((byte)(number % 10));

	result[length] = '\0';
	return result;
}

WString WString::NumericString(int number)
{
	size_t length = WString::GetLength(number);
	size_t naturalNumber = number < 0 ? -number : number;

	WString result(length);

	for (int i = length - 1; i > 0; i--, naturalNumber /= 10)
		result[i] = DigitToChar(naturalNumber % 10);

	if (number < 0)
		result[0] = '-';
	else
		result[0] = DigitToChar(naturalNumber % 10);

	result[length] = '\0';
	return result;
}

WString WString::NumericString(double number)
{
	return NumericString(number, DEFAULT_PRECISION);
}

WString WString::NumericString(double number, size_t precision)
{
	int wholePart = (int)number;
	size_t length = GetLength(wholePart), resultLength = length + 1 + precision;
	if (wholePart == 0 && number < 0)
		length++;
	size_t naturalNumber = wholePart < 0 ? -wholePart : wholePart;
	WString result(resultLength);

	for (int i = length - 1; i >= 0; i--, naturalNumber /= 10)
		result[i] = DigitToChar(naturalNumber % 10);

	if (number < 0)
		result[0] = '-';

	result[length] = '.';

	double decimalPart = number - wholePart, 
		absDecimalPart = decimalPart < 0 ? -decimalPart : decimalPart;
	for (size_t i = 0; i < precision; i++)
	{
		uint8_t digit = (uint8_t)(absDecimalPart *= 10);
		absDecimalPart -= digit;
		result[length + 1 + i] = DigitToChar(digit);
	}
	return result;
}

bool WString::IsEscapeChar(wchar_t symbol)
{
	return symbol == '\"' || symbol == '\'' || symbol == '\\';
}

WString operator+(const WString& lhs, const WString& rhs)
{
	size_t thisLen = lhs.Length(), thatLen = rhs.Length(), totalLen = thisLen + thatLen;
	WString result(totalLen);
	for (size_t i = 0; i < thisLen; i++)
		result[i] = lhs[i];
	for (size_t i = thisLen; i <= totalLen; i++)
		result[i] = rhs[i - thisLen];
	return result;
}

std::wistream& operator>>(std::wistream& input, WString& string)
{
	wchar_t buffer[1024];
	input >> buffer;
	string = buffer;	
    return input;
}

WString::~WString()
{
	FreeMemberData();
}

std::wostream& operator<<(std::wostream& output, const WString& string)
{
	return output << string.C_Str();
}

bool operator==(const WString& lhs, const WString& rhs)
{
	return wcscmp(lhs, rhs) == 0;
}

bool operator!=(const WString& lhs, const WString& rhs)
{
	return !(lhs == rhs);
}

bool operator<(const WString& lhs, const WString& rhs)
{
	return wcscmp(lhs, rhs) < 0;
}

bool operator>(const WString& lhs, const WString& rhs)
{
	return wcscmp(lhs, rhs) > 0;
}

bool operator<=(const WString& lhs, const WString& rhs)
{
	return lhs == rhs || lhs < rhs;
}

bool operator>=(const WString& lhs, const WString& rhs)
{
	return lhs == rhs || lhs > rhs;
}

bool operator==(const WString& lhs, const wchar_t* rhs)
{
	return wcscmp(lhs, rhs) == 0;
}

bool operator!=(const WString& lhs, const wchar_t* rhs)
{
	return !(lhs == rhs);
}

bool operator<(const WString& lhs, const const wchar_t* rhs)
{
	return wcscmp(lhs, rhs) < 0;
}

bool operator>(const WString& lhs, const wchar_t* rhs)
{
	return wcscmp(lhs, rhs) > 0;
}

bool operator<=(const WString& lhs, const wchar_t* rhs)
{
	return lhs == rhs || lhs < rhs;
}

bool operator>=(const WString& lhs, const wchar_t* rhs)
{
	return lhs == rhs || lhs > rhs;
}

std::wistream& ReadLine(std::wistream& input, WString& string, wchar_t delim)
{
	wchar_t buffer[1024];
	input.getline(buffer, 1024, delim);
	string = buffer;
	return input;
}

const wchar_t& WString::WStringView::operator[](unsigned index) const
{
	return data[index];
}

WString::WStringView WString::WStringView::SubstringView(unsigned startIndex) const
{
	if (startIndex >= length)
		throw std::runtime_error("Invalid index");
	WStringView view;
	view.data = data + startIndex;
	view.length = length - startIndex;
	return view;
}

WString::WStringView WString::WStringView::SubstringView(unsigned startIndex, unsigned length) const
{
	size_t len = this->length;
	if (startIndex >= len)
		throw std::runtime_error("Invalid index");
	WStringView view;
	view.data = data + startIndex;
	view.length = (startIndex + length < len) ? length : len - startIndex;
	return view;
}