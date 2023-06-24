#pragma once
#include <fstream>
#include "IInterfacable.h"
#include "../File managers/FileManager.h"
#include "../File managers/TableFileManager.h"

class SpreadsheetsInterface : public IInterfacable
{
	static const size_t COMMANDS_COUNT = 6;
	static const String COMMANDS[COMMANDS_COUNT];

	void (SpreadsheetsInterface::* Operations[COMMANDS_COUNT])(const Vector<String>& arguments) =
	{
		&SpreadsheetsInterface::Open,
		&SpreadsheetsInterface::Save,
		&SpreadsheetsInterface::Print,
		&SpreadsheetsInterface::Edit,
		&SpreadsheetsInterface::Add,
		&SpreadsheetsInterface::Close
	};

	private:
		FileManager* fileManager = new TableFileManager();

	public:
		void ExecuteCommand(const String& command, const Vector<String>& arguments) override;
		void Open(const Vector<String>& arguments);
		void Save(const Vector<String>& arguments);
		void Print(const Vector<String>& arguments);
		void Edit(const Vector<String>& arguments);
		void Add(const Vector<String>& arguments);
		void Close(const Vector<String>& arguments);
		~SpreadsheetsInterface();
};
