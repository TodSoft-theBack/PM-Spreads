#pragma once
#include <fstream>
#include "String.h"
#include "IInterfacable.h"
#include "Table.h"
class SpreadsheetsInterface : public IInterfacable
{
	static const size_t COMMANDS_COUNT = 6;
	static const String COMMANDS[COMMANDS_COUNT];

	void (SpreadsheetsInterface::* Operations[COMMANDS_COUNT])(const Vector<String>& arguments) =
	{
		&SpreadsheetsInterface::Open,
		&SpreadsheetsInterface::Save,
		&SpreadsheetsInterface::Print,
		&SpreadsheetsInterface::Close,
		&SpreadsheetsInterface::Exit,
	};

	private:
		Table table;
		std::fstream file;

	public:
		void ExecuteCommand(const String& command, const Vector<String>& arguments) override;
		void Open(const Vector<String>& arguments);
		void Save(const Vector<String>& arguments);
		void Print(const Vector<String>& arguments);
		void Close(const Vector<String>& arguments);
		void Exit(const Vector<String>& arguments);
		~SpreadsheetsInterface() = default;
};

