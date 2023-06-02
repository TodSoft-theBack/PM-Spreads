#include "Application.h"

const char Application::DEFAULT_APPLICATION_NAME[] = "Application interface";
const char Application::DEFAULT_COMMAND_STRING[] = "Command Listener";
const char Application::DEFAULT_EXIT_COMMAND[] = "Quit";

void Application::SetApplicationName(const String& applicationName)
{
	_applicationName = applicationName;
}

void Application::SetCommandString(const String& commandString)
{
	_commandString = commandString;
}

void Application::SetExitCommand(const String& exitCommand)
{
	_exitCommand = exitCommand;
}

void Application::SetInterface(IInterfacable* const interfacePointer)
{
	this->_interface = interfacePointer;
}

void Application::Run()
{
	std::cout << "Starting " << _applicationName <<"..." << std::endl;

	String line;
	String command;
	do
	{
		std::cout << std::endl << "@" << _commandString << "> ";
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
			command = std::move(line.SubstringConst(0, commandIndex).Trim());
			arguments = line.SubstringConst(commandIndex + 1).Trim().Split();
		}

		if (command == _exitCommand)
			break;

		if (_interface != nullptr)
			try 
			{
				_interface->ExecuteCommand(command, arguments);
			}
			catch (std::runtime_error error)
			{
				std::cout << error.what() << std::endl;
			}
	} while (true);
	std::cout << std::endl << "Exiting " << _applicationName << "..." << std::endl;
}

Application::~Application()
{
	delete _interface;
	_interface = nullptr;
}
