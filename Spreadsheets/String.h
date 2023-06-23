#pragma once
#include "Vector.hpp"
#include <iostream>
typedef uint8_t byte;

class StringIterator
{
	private:
		const char* pointer = nullptr;
		unsigned counter = 0;

	public:
		StringIterator() = default;
		StringIterator(const char* pointer) : pointer(pointer) { }
		StringIterator(const char* pointer, size_t length) : pointer (pointer), counter(length) { }
		StringIterator& operator++() { counter++; return *this; }
		StringIterator operator++(int) { StringIterator copy = *this; counter++; return copy; }
		StringIterator& operator--() { counter--; return *this; }
		StringIterator operator--(int) { StringIterator copy = *this; counter--; return copy; }
		const char& operator[](unsigned index) { return pointer[index]; }
		const char* operator->() { return (pointer + counter); }
		const char& operator*() { return *(pointer + counter); }
		bool operator==(const StringIterator& iterator) { return pointer == iterator.pointer && counter == iterator.counter; }
		bool operator!=(const StringIterator& iterator) { return pointer != iterator.pointer || counter != iterator.counter; }
};

class String
{
	public:
		using Iterator = StringIterator;
		static const size_t DEFAULT_PRECISION = 2;
		static const byte SMALL_STRING_MAX_SIZE = sizeof(size_t) + sizeof(char*) + sizeof(size_t) - 1; 

		struct StringView
		{
			const char* data;
			size_t length;
			const char& operator[](unsigned index) const;
			StringView SubstringView(unsigned startIndex) const;
			StringView SubstringView(unsigned startIndex, unsigned length) const;
		};

		enum struct NumericType 
		{
			Integer,
			Decimal,
			NaN
		};

    private:
        char* _data = nullptr;
	    size_t _length = 0;
		size_t _capacity = 0;

	    void CopyMemberData(const String& copy);
	    void FreeMemberData();
		void MoveMemberData(String&& temporary) noexcept;
		bool IsSmallString() const;
		byte LengthByte() const;
		byte LastByteOf(size_t variable) const;
		byte& LastByteOf(size_t& variable);
		byte& LengthByte();

		//For small strings
		char CharAt(unsigned index) const; 
		char& CharAt(unsigned index);
		
    public:
	    String();
		explicit String(size_t length);
	    String(const char* string);
		String(const StringView& string);
		String(const Vector<char>& collection);
	    String(const String& string);
		String(String&& temporary) noexcept;

	    size_t Length() const;
		size_t Capacity() const;
		StringView SubstringView(unsigned startIndex, size_t length) const;
		StringView SubstringView(unsigned startIndex) const;
		String Substring(unsigned startIndex, size_t length) const;
		String Substring(unsigned startIndex) const;
		String& operator=(const String& rhs);
		String& operator=(String&& rhs) noexcept;
		String& operator+=(const String& rhs);
		String& operator+=(char rhs);
	    char operator[](unsigned index) const;
		char& operator[](unsigned index);
		char First() const;
		char Last() const;
		operator const char* () const;
		StringView GetStringView() const;
		const char* C_Str() const;
		size_t CountChar(char symbol) const;
		int IndexOf(char symbol, unsigned startIndex) const;
		int IndexOf(char symbol) const;
		int LastIndexOf(char symbol, unsigned startIndex) const; 
		int LastIndexOf(char symbol) const;
		void Trim();
		static String Trim(const String& string);
		static String Trim(const StringView& string);
		Vector<String> Split(char delim = ' ') const;
		bool IsEmpty() const;
		NumericType CheckType() const;
		static bool IsAllowedInInteger(char symbol, unsigned index);
		bool IsInteger() const;
		int IntegerParse() const;
		static bool IsAllowedInDecimal(char symbol, bool& hasDecimalsAlready, unsigned index);
		bool IsDecimal() const;
		double DecimalParse() const;
		static String NumericString(size_t number);
		static String NumericString(int number);
		static String NumericString(double number);
		static String NumericString(double number, size_t precision);
		static bool IsDigit(char symbol);
		static byte CharToDigit(char symbol);
		static char DigitToChar(byte digit);
		static size_t GetLength(size_t number);
		static size_t GetLength(int number);
		Iterator begin() const { return Iterator(C_Str()); }
		Iterator end() const { return Iterator(C_Str(), Length()); }
		friend String operator+(const String& lhs, const String& rhs);
		friend std::istream& operator>>(std::istream& input, String& string);
	    ~String();
};

std::ostream& operator<<(std::ostream& output, const String& string);

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);

bool operator==(const String& lhs, const char* rhs);
bool operator!=(const String& lhs, const char* rhs);
bool operator<(const String& lhs, const char* rhs);
bool operator>(const String& lhs, const char* rhs);
bool operator<=(const String& lhs, const char* rhs);
bool operator>=(const String& lhs, const char* rhs);

std::istream& ReadLine(std::istream& input, String& string, char delim = '\n');