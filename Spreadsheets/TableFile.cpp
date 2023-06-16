#include "TableFile.h"

TableFile::TableFile(const char* filepath) : File(filepath)
{
	size_t lines = CountLines();
	String line;
	ReadLine(stream, line);
	size_t columns = line.CountChar(',') + 1;
	table = std::move(Table(lines, columns));
	table[0] = Row::ParseLine(line, columns);
	for (size_t i = 1; i < lines; i++)
	{
		ReadLine(stream, line);
		table[i] = Row::ParseLine(line, columns);
	}
}

File* TableFile::Clone() const
{
	return new TableFile(filename.C_Str());
}

void TableFile::EditAtPos(unsigned row, unsigned column, const char* newValue)
{
	table[row][column] = CellFactory::CreateCell(newValue);
}

std::ostream& TableFile::Print(std::ostream& output) const
{
	return output << table;
}

TableFile::~TableFile()
{
	stream.close();
}
