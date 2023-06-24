#pragma once
#include <windows.h>
#include <sstream>
#include "../Generic/String.h"
#include "IInterfacable.h"

class Application
{

	static const char DEFAULT_APPLICATION_NAME[];
	static const char DEFAULT_COMMAND_STRING[];
	static const char DEFAULT_EXIT_COMMAND[];

	String _applicationName = DEFAULT_APPLICATION_NAME;
	String _commandString = DEFAULT_COMMAND_STRING;
	String _exitCommand = DEFAULT_EXIT_COMMAND;
	IInterfacable* _interface = nullptr;

	static Vector<String> SplitToArguments(const String& string);

	public:
		Application() = default;
		Application(const Application& appInterface) = delete;
		Application(Application&& appInterface) = delete;
		Application& operator=(const Application& appInterface) = delete;
		Application& operator=(Application&& appInterface) = delete;
		void SetApplicationName(const String& applicationName);
		void SetCommandString(const String& commandString);
		void SetExitCommand(const String& exitCommand);
		void SetInterface(IInterfacable* const interfacePointer);
		void Run();
		~Application();
};