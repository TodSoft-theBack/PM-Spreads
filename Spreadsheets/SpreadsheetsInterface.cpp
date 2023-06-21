#include "SpreadsheetsInterface.h"

const String SpreadsheetsInterface::COMMANDS[COMMANDS_COUNT] = { "Open", "Save","Print", "Edit", "Close" };

void SpreadsheetsInterface::ExecuteCommand(const String& command, const Vector<String>& arguments)
{
	for (size_t i = 0; i < COMMANDS_COUNT; i++)
		if (command == COMMANDS[i])
		{
			(this->*Operations[i])(arguments);
			return;
		}
	throw std::runtime_error("No such command found!!!");
}

void SpreadsheetsInterface::Open(const Vector<String>& arguments)
{
	size_t argCount = arguments.Count();

	if (argCount != 1)
		throw std::runtime_error("No command with such arguments");
	fileManager->OpenFile(arguments[0]);
}

void SpreadsheetsInterface::Save(const Vector<String>& arguments)
{
	size_t argCount = arguments.Count();
	if (argCount == 1)
	{
		fileManager->Save(arguments[0]);
		return;
	}

	if (argCount != 3)
		throw std::runtime_error("No command with such arguments");

	if (arguments[1] != "as")
		throw std::runtime_error("No command with such arguments");
	fileManager->SaveAs(arguments[0], arguments[2]);
	std::cout << "Executed on " << arguments;
}

void SpreadsheetsInterface::Print(const Vector<String>& arguments)
{
	size_t argCount = arguments.Count();
	if (argCount != 1)
		throw std::runtime_error("No command with such arguments");
	fileManager->PrintFile(std::cout, arguments[0]);
}

void SpreadsheetsInterface::Edit(const Vector<String>& arguments)
{
	size_t argCount = arguments.Count();
	if (argCount != 4)
		throw std::runtime_error("No command with such arguments");
	if (!arguments[1].IsInteger() || !arguments[2].IsInteger())
		throw std::runtime_error("Please provide valid row and columns!");

	size_t row = arguments[1].IntegerParse() - 1, column = arguments[2].IntegerParse() - 1;

	if (row < 0 || column < 0)
		throw std::runtime_error("Only 1 based indecies allowed!!");

	fileManager->Edit(arguments[0], row, column, arguments[3]);
}

void SpreadsheetsInterface::Close(const Vector<String>& arguments)
{
	size_t argCount = arguments.Count();
	if (argCount != 1)
		throw std::runtime_error("No command with such arguments!");
	fileManager->CloseFile(arguments[0]);
}

SpreadsheetsInterface::~SpreadsheetsInterface() 
{
	delete fileManager;
}