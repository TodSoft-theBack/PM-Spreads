#include "ApplicationInterface.h"

const char ApplicationInterface::DEFAULT_NAME[] = "Application interface";
const char ApplicationInterface::DEFAULT_COMMAND_STRING[] = "Table parser";

ApplicationInterface::ApplicationInterface(const String& applicationName, const String& commandString) 
	: name(applicationName), commandStirng(commandStirng)
{
}

ApplicationInterface::ApplicationInterface(String&& applicationName, String&& commandString) 
	: name(std::move(applicationName)), commandStirng(std::move(commandStirng))
{
}


void ApplicationInterface::Run()
{
	std::cout << "Starting " << name <<"..." << std::endl;

	String line;
	String command;
	do
	{
		std::cout << std::endl << "@Table parser > ";
		line = String(std::cin);
		line.Trim();
		if (line.Length() == 0)
			continue;

		Vector<String> arguments;
		int commandIndex = line.IndexOf(' ');
		if (commandIndex == -1)
			command = line;
		else
		{
			command = std::move(line.Substring(0, commandIndex));
			command.Trim();
			arguments = line.Substring(commandIndex, line.Length() - commandIndex).Split(' ');
		}
		if (strcmp(command.C_Str(), "Quit") == 0)
			break;

		if (_interface != nullptr)
			_interface->ExecuteCommand(command, arguments);
	} while (true);
	std::cout << "Exiting " << name << "..." << std::endl;
}

ApplicationInterface::~ApplicationInterface()
{
	delete _interface;
	_interface = nullptr;
}
