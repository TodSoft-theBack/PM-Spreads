#pragma once
#include "File.h"
#include "Table.h"

class TableFile : public File
{
	public:
		Table table;
		TableFile(const char* filepath);
		File* Clone() const override;
		void EditAtPos(unsigned row, unsigned column, const char* newValue) override;
		void AddEmptyLine() override;
		void AddEmptyColumn() override;
		void InsertLineAt(size_t index) override;
		void InsertColumnAt(size_t index) override;
		void SaveAs(const char* filename) override;
		std::ostream& Print(std::ostream& output) override;
		~TableFile();
};

