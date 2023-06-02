#pragma once
#include <fstream>
#include "IInterfacable.h"
#include "Table.h"
class SpreadsheetsInterface : public IInterfacable
{
	private:
		Table table; 
		std::fstream file;
	public:
		void ExecuteCommand(const String& command, const Vector<String>& arguments) override;
};

