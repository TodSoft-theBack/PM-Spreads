#pragma once
#include "File.h"
#include "../Table/Table.h"

class TableFile : public File
{
	public:
		Table table;
		TableFile(const char* filepath);
		File* Clone() const override;
		void EditAtPos(unsigned row, unsigned column, const char* newValue) override;
		void AddEmptyLine() override;
		void AddEmptyColumn() override;
		void SaveAs(const char* filename) override;
		std::ostream& Print(std::ostream& output) override;
		~TableFile();
};
