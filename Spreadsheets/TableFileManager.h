#pragma once
#include "FileManager.h"
#include "TableFile.h"

class TableFileManager : public FileManager
{
	public:
		TableFileManager();
		void OpenFile(const char* filepath) override;
		void PrintFile(std::ostream& output, const char* filepath) override;
		void Edit(const char* filepath, unsigned line, unsigned column, const char* newValue) override;
		void Save(const char* filepath) override;
		void SaveAs(const char* originalfilePath, const char* newFilePath) override;
		void CloseFile(const char* filepath) override;
		~TableFileManager();
};

