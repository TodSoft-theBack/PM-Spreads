#include "TableFile.h"

TableFile::TableFile(const char* filepath) : File(filepath)
{
	size_t lines = CountLines();
	String line;
	table = Table(lines);
	for (size_t i = 0; i < lines; i++)
	{
		size_t columns = table.Columns();
		ReadLine(stream, line);
		if (line.IsEmpty())
			table.AddRow(i);
		else
			table.AddRow(Row::ParseLine(line, i, columns));
	}
}

File* TableFile::Clone() const
{
	return new TableFile(filename.C_Str());
}

void TableFile::EditAtPos(unsigned row, unsigned column, const char* newValue)
{
	table[row][column] = CellFactory::CreateCell(newValue);
	size_t length = strlen(newValue);
}

void TableFile::AddEmptyLine()
{
	table.AddRow();
}

void TableFile::AddEmptyColumn()
{
	table.AddColumn();
}

void TableFile::SaveAs(const char* filename)
{
	if (stream.is_open())
		stream.close();
	stream.open(filename, std::ios::out);
	size_t rows = table.Rows(), columns = table.Columns();
	for (size_t row = 0; row < rows; row++)
	{
		for (size_t column = 0; column < columns; column++)
			stream << table[row][column]->ToString() << (column < columns - 1 ? ", " : "");
		stream << std::endl;
	}
	stream.close();
}

std::ostream& TableFile::Print(std::ostream& output)
{
	return output << table;
}

TableFile::~TableFile()
{
	stream.close();
}