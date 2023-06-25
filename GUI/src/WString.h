#pragma once
#include <iostream>
typedef uint8_t byte;

class WStringIterator
{
	private:
		const wchar_t* pointer = nullptr;
		unsigned counter = 0;

	public:
		WStringIterator() = default;
		WStringIterator(const wchar_t* pointer) : pointer(pointer) { }
		WStringIterator(const wchar_t* pointer, size_t length) : pointer (pointer), counter(length) { }
		WStringIterator& operator++() { counter++; return *this; }
		WStringIterator operator++(int) { WStringIterator copy = *this; counter++; return copy; }
		WStringIterator& operator--() { counter--; return *this; }
		WStringIterator operator--(int) { WStringIterator copy = *this; counter--; return copy; }
		const wchar_t& operator[](unsigned index) { return pointer[index]; }
		const wchar_t* operator->() { return (pointer + counter); }
		const wchar_t& operator*() { return *(pointer + counter); }
		bool operator==(const WStringIterator& iterator) { return pointer == iterator.pointer && counter == iterator.counter; }
		bool operator!=(const WStringIterator& iterator) { return pointer != iterator.pointer || counter != iterator.counter; }
};

class WString
{
	public:
		using Iterator = WStringIterator;
		static const size_t DEFAULT_PRECISION = 2;
		static const byte SMALL_STRING_MAX_SIZE = sizeof(size_t) + sizeof(wchar_t*) + sizeof(size_t) - 1; 

		struct WStringView
		{
			const wchar_t* data;
			size_t length;
			const wchar_t& operator[](unsigned index) const;
			WStringView SubstringView(unsigned startIndex) const;
			WStringView SubstringView(unsigned startIndex, unsigned length) const;
		};

		enum struct NumericType 
		{
			Integer,
			Decimal,
			NaN
		};

    private:
        wchar_t* _data = nullptr;
	    size_t _length = 0;
		size_t _capacity = 0;

	    void CopyMemberData(const WString& copy);
	    void FreeMemberData();
		void MoveMemberData(WString&& temporary) noexcept;
		bool IsSmallString() const;
		byte LengthByte() const;
		byte LastByteOf(size_t variable) const;
		byte& LastByteOf(size_t& variable);
		byte& LengthByte();

		//For small strings
		wchar_t wchar_tAt(unsigned index) const; 
		wchar_t& wchar_tAt(unsigned index);
		
    public:
	    WString();
		explicit WString(size_t length);
	    WString(const wchar_t* string);
		WString(const WStringView& string);
	    WString(const WString& string);
		WString(WString&& temporary) noexcept;

	    size_t Length() const;
		size_t Capacity() const;
		WStringView SubstringView(unsigned startIndex, size_t length) const;
		WStringView SubstringView(unsigned startIndex) const;
		WString Substring(unsigned startIndex, size_t length) const;
		WString Substring(unsigned startIndex) const;
		WString& operator=(const WString& rhs);
		WString& operator=(WString&& rhs) noexcept;
		WString& operator+=(const WString& rhs);
		WString& operator+=(wchar_t rhs);
	    wchar_t operator[](unsigned index) const;
		wchar_t& operator[](unsigned index);
		wchar_t First() const;
		wchar_t Last() const;
		operator const wchar_t* () const;
		WStringView GetStringView() const;
		const wchar_t* C_Str() const;
		size_t Countwchar_t(wchar_t symbol) const;
		int IndexOf(wchar_t symbol, unsigned startIndex) const;
		int IndexOf(wchar_t symbol) const;
		int LastIndexOf(wchar_t symbol, unsigned startIndex) const; 
		int LastIndexOf(wchar_t symbol) const;
		void Trim();
		static WString Trim(const WString& string);
		static WString Trim(const WStringView& string);
		bool IsEmpty() const;
		NumericType CheckType() const;
		static bool IsAllowedInInteger(wchar_t symbol, unsigned index);
		bool IsInteger() const;
		int IntegerParse() const;
		static bool IsAllowedInDecimal(wchar_t symbol, bool& hasDecimalsAlready, unsigned index);
		bool IsDecimal() const;
		double DecimalParse() const;
		static WString NumericString(size_t number);
		static WString NumericString(int number);
		static WString NumericString(double number);
		static WString NumericString(double number, size_t precision);
		static bool IsEscapeChar(wchar_t symbol);
		static bool IsDigit(wchar_t symbol);
		static byte CharToDigit(wchar_t symbol);
		static wchar_t DigitToChar(byte digit);
		static size_t GetLength(size_t number);
		static size_t GetLength(int number);
		Iterator begin() const { return Iterator(C_Str()); }
		Iterator end() const { return Iterator(C_Str(), Length()); }
		friend WString operator+(const WString& lhs, const WString& rhs);
		friend std::wistream& operator>>(std::wistream& input, WString& string);
	    ~WString();
};

std::wostream& operator<<(std::wostream& output, const WString& string);

bool operator==(const WString& lhs, const WString& rhs);
bool operator!=(const WString& lhs, const WString& rhs);
bool operator<(const WString& lhs, const WString& rhs);
bool operator>(const WString& lhs, const WString& rhs);
bool operator<=(const WString& lhs, const WString& rhs);
bool operator>=(const WString& lhs, const WString& rhs);

bool operator==(const WString& lhs, const wchar_t* rhs);
bool operator!=(const WString& lhs, const wchar_t* rhs);
bool operator<(const WString& lhs, const wchar_t* rhs);
bool operator>(const WString& lhs, const wchar_t* rhs);
bool operator<=(const WString& lhs, const wchar_t* rhs);
bool operator>=(const WString& lhs, const wchar_t* rhs);

std::wistream& ReadLine(std::wistream& input, WString& string, wchar_t delim = '\n');