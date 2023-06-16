#include "FileManager.h"

void FileManager::Resize(size_t size)
{
	File** newCollection = new File * [size];
	for (size_t i = 0; i < _count; i++)
		newCollection[i] = files[i]->Clone();
	delete[] files;
	files = newCollection;
}

File*& FileManager::operator[](const char* filepath)
{
	size_t count = _count;
	for (size_t i = 0; i < count; i++)
		if (files[i]->Filename() == filepath)
			return files[i];
	throw std::runtime_error("No such file is opened");
}

File*& FileManager::operator[](unsigned index)
{
	return files[index];
}

FileManager::~FileManager()
{
	for (size_t i = 0; i < _count; i++)
		delete files[i];
	delete[] files;
	files = nullptr;
}
