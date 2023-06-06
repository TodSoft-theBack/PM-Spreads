#include "SpreadsheetsInterface.h"

const String SpreadsheetsInterface::COMMANDS[COMMANDS_COUNT] = { "Open", "Save", "Close", "Exit" };

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
	std::cout << "Executed on "  << arguments;

	file.open(arguments[0].C_Str(), std::ios::in | std::ios::_Nocreate);
	if (!file.is_open())
		throw std::runtime_error("Invalid filename");
}

void SpreadsheetsInterface::Save(const Vector<String>& arguments)
{
	std::cout << "Executed on " << arguments;
}

void SpreadsheetsInterface::Print(const Vector<String>& arguments)
{
	std::cout << "Executed on " << arguments;
}

void SpreadsheetsInterface::Close(const Vector<String>& arguments)
{
	std::cout << "Executed on " << arguments;
}

void SpreadsheetsInterface::Exit(const Vector<String>& arguments)
{
	std::cout << "Executed on " << arguments;
}