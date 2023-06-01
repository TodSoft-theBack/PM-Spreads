#pragma once
#include<sstream>
#include "String.h"
#include "IInterfacable.h"

class ApplicationInterface
{

	static const char DEFAULT_NAME[];
	static const char DEFAULT_COMMAND_STRING[];

	String name = DEFAULT_NAME;
	String commandStirng = DEFAULT_COMMAND_STRING;
	IInterfacable* _interface = nullptr;

	public:
		ApplicationInterface() = default;
		ApplicationInterface(const ApplicationInterface& appInterface) = delete;
		ApplicationInterface(const String& applicationName, const String& commandString = DEFAULT_COMMAND_STRING);
		ApplicationInterface(String&& applicationName, String&& commandString = DEFAULT_COMMAND_STRING);
		ApplicationInterface& operator=(const ApplicationInterface& appInterface) = delete;
		void Run();
		~ApplicationInterface();
};