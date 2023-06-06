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
	std::cout << "Executed on "  << arguments;
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