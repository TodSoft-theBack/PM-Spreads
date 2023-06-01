#pragma once
#include <iostream>
#include "Vector.hpp"
typedef uint8_t byte;

class String
{
	public:
		static const byte SMALL_STRING_MAX_SIZE = sizeof(size_t) + sizeof(char*) + sizeof(size_t); 
		struct StringView
		{
			const char* data;
			size_t length;
		};

    private:
        char* _data = nullptr;
	    size_t _length = 0;
		size_t _capacity = 0;

	    void CopyMemberData(const String& copy);
	    void FreeMemberData();
		void MoveMemberData(String&& temporary);
		bool IsSmallString() const;
		byte LengthByte() const;
		byte LastByteOf(size_t variable) const;
		byte& LastByteOf(size_t& variable);
		byte& LengthByte();

		// Only for small strings
		char CharAt(unsigned index) const; 
		char& CharAt(unsigned index);
		
    public:
	    String();
		String(size_t capacity);
	    String(const char* string);
		String(std::istream& input);
	    String(const String& string);
		String(String&& temporary);

	    size_t Length() const;
		StringView SubStringView(unsigned startIndex, size_t length);
		String Substring(unsigned startIndex, size_t length);
		
		String& operator=(const String& rhs);
		String& operator=(String&& rhs);
		String& operator+=(const String& rhs);
	    char operator[](unsigned index) const;
		char& operator[](unsigned index);
		const char* C_Str() const;
		int IndexOf(char symbol) const;
		void Trim();
		String Trim() const;
		Vector<String> Split(char delim);
		
		friend String operator+(const String& lhs, const String& rhs);
        friend std::ostream& operator<<(std::ostream& output, const String& string);
		friend std::istream& operator>>(std::istream& input, String& string);
		
	    ~String();
};