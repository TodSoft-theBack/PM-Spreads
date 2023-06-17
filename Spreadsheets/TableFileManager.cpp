#include "TableFileManager.h"

TableFileManager::TableFileManager()
{
	files = new File* [_capacity];
}

void TableFileManager::OpenFile(const char* filepath)
{
	File* file = new TableFile(filepath);
	if (!file->Stream().is_open())
		throw std::runtime_error("Could not open file!");
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
			delete files[i];
			std::swap(files[i], files[--_count]);
		}
	}
	
}

TableFileManager::~TableFileManager()
{

}
