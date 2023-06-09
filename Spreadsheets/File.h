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
		std::fstream& Stream();
		const String& Filename() const;
		const bool& HasChanged() const;
		size_t CountMentions(char symbol);
		size_t CountLines();
		virtual std::ostream& Print(std::ostream& output);
		virtual void EditAtPos(unsigned lineIndex, unsigned rowPos, const char* newValue); 
		virtual void AddEmptyLine() = 0;
		virtual void AddEmptyColumn() = 0;
		virtual void InsertLineAt(size_t index) = 0;
		virtual void InsertColumnAt(size_t index) = 0;
		virtual void SaveAs(const char* filename) = 0;
		virtual File* Clone() const = 0;
		virtual ~File();
};

