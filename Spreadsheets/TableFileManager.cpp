#include "TableFileManager.h"

TableFileManager::TableFileManager()
{
	files = new File* [_capacity];
}

void TableFileManager::OpenFile(const char* filepath)
{
	File* file = new TableFile(filepath);
	if (_count == _capacity)
		Resize(_capacity * 2);
	files[_count++] = file;
}

void TableFileManager::PrintFile(std::ostream& output, const char* filepath)
{
	File* file = operator[](filepath);
	file->Print(output);
}

void TableFileManager::Edit(const char* filepath, unsigned row, unsigned column, const char* newValue)
{
	File* file = operator[](filepath);
	file->EditAtPos(row, column, newValue);
}

void TableFileManager::Save(const char* filepath)
{
	File* file = operator[](filepath);
	file->SaveAs(filepath);
}

void TableFileManager::SaveAs(const char* originalfilePath, const char* newFilePath)
{
	File* file = operator[](originalfilePath);
	file->SaveAs(newFilePath);
}

void TableFileManager::CloseFile(const char* filepath)
{
	for (size_t i = 0; i < _count; i++)
	{
		File* currentFile = files[i];
		if (currentFile->Filename() == filepath)
		{
			if (currentFile->HasChanged())
				throw std::runtime_error("Unsaved changes are present Cannot close");
			delete currentFile;
			std::swap(files[i], files[--_count]);
			return;
		}
	}
	throw std::runtime_error("No such file is opened");
}

