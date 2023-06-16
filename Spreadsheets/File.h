#pragma once
#include <fstream>
#include "String.h"

class File
{
	protected:
		std::fstream stream;
		String filename;
		bool hasChanged = false;
	public:
		
		File(const char* path);
		File(const File& copy) = delete;
		File& operator= (const File& file) noexcept = delete;
		const std::fstream& Stream() const;
		const String& Filename() const;
		const bool& HasChanged() const;
		bool& HasChanged();
		size_t CountMentions(char symbol);
		size_t CountLines();
		virtual std::ostream& Print(std::ostream& output) const;
		virtual void EditAtPos(unsigned lineIndex, unsigned rowPos, const char* newValue);
		virtual File* Clone() const = 0;
		virtual ~File();
};

