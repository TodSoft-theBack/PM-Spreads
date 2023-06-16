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
		std::ostream& Print(std::ostream& output) const override;
		~TableFile();
};

