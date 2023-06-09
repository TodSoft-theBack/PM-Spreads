#pragma once
#include <fstream>
#include "IInterfacable.h"
#include "String.h"
#include "Table.h"
#include "FileManager.h"
#include "TableFileManager.h"

class SpreadsheetsInterface : public IInterfacable
{
	static const size_t COMMANDS_COUNT = 7;
	static const String COMMANDS[COMMANDS_COUNT];

	void (SpreadsheetsInterface::* Operations[COMMANDS_COUNT])(const Vector<String>& arguments) =
	{
		&SpreadsheetsInterface::Open,
		&SpreadsheetsInterface::Save,
		&SpreadsheetsInterface::Print,
		&SpreadsheetsInterface::Edit,
		&SpreadsheetsInterface::Add,
		&SpreadsheetsInterface::Insert,
		&SpreadsheetsInterface::Close
	};

	private:
		TableFileManager* fileManager = new TableFileManager();

	public:
		void ExecuteCommand(const String& command, const Vector<String>& arguments) override;
		void Open(const Vector<String>& arguments);
		void Save(const Vector<String>& arguments);
		void Print(const Vector<String>& arguments);
		void Edit(const Vector<String>& arguments);
		void Add(const Vector<String>& arguments);
		void Insert(const Vector<String>& arguments);
		void Close(const Vector<String>& arguments);
		~SpreadsheetsInterface();
};

