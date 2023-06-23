#pragma once
#include "File.h"
#include "String.h"
#include "Vector.hpp"

class FileManager
{
	static const size_t DEFAULT_CAPACITY = 8;
	protected:
		File** files = nullptr;
		size_t _count = 0;
		size_t _capacity = DEFAULT_CAPACITY;
		void Resize(size_t size);

	public:
		FileManager() = default;
		FileManager(const FileManager&) = delete;
		FileManager& operator=(const FileManager&) = delete;
		virtual void OpenFile(const char* filepath) = 0;
		File*& operator[](const char* filepath);
		File*& operator[](unsigned index);
		virtual void PrintFile(std::ostream& output, const char* filepath) = 0;
		virtual void Edit(const char* filepath, unsigned lineIndex, unsigned columnPos, const char* newValue) = 0;
		virtual void AddNewLine(const char* filepath) = 0;
		virtual void AddNewColumn(const char* filepath) = 0;
		virtual void Save(const char* filepath) = 0;
		virtual void SaveAs(const char*  originalfilePath, const char* newFilePath) = 0;
		virtual void CloseFile(const char* filepath) = 0;
		virtual ~FileManager();
};

