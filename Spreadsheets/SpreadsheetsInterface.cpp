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
	fileManager->OpenFile(arguments[0].C_Str());
}

void SpreadsheetsInterface::Save(const Vector<String>& arguments)
{
	size_t argCount = arguments.Count();
	if (argCount == 1)
	{
		fileManager->Save(arguments[0].C_Str());
		return;
	}

	if (argCount != 3)
		throw std::runtime_error("No command with such arguments");

	if (arguments[1] != "as")
		throw std::runtime_error("No command with such arguments");
	fileManager->SaveAs(arguments[0].C_Str(), arguments[2].C_Str());
	std::cout << "Executed on " << arguments;
}

void SpreadsheetsInterface::Print(const Vector<String>& arguments)
{
	size_t argCount = arguments.Count();
	if (argCount != 1)
		throw std::runtime_error("No command with such arguments");
	fileManager->PrintFile(std::cout, arguments[0].C_Str());
}

void SpreadsheetsInterface::Edit(const Vector<String>& arguments)
{
	size_t argCount = arguments.Count();
	if (argCount != 4)
		throw std::runtime_error("No command with such arguments");
	if (!arguments[1].IsInteger() || !arguments[2].IsInteger())
		throw std::runtime_error("Please provide valid row and columns!");

	size_t row = arguments[1].IntegerParse(), column = arguments[2].IntegerParse();

	fileManager->Edit(arguments[0].C_Str(), row, column, arguments[3].C_Str());
}

void SpreadsheetsInterface::Close(const Vector<String>& arguments)
{
	size_t argCount = arguments.Count();
	if (argCount != 1)
		throw std::runtime_error("No command with such arguments!");
	fileManager->CloseFile(arguments[0].C_Str());
}

SpreadsheetsInterface::~SpreadsheetsInterface() 
{
	delete fileManager;
}