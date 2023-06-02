#include <iostream>
#include "ApplicationInterface.h"
#include "SpreadsheetsInterface.h"

int main()
{
	Application _interface;
	_interface.SetApplicationName("PM Spreads");
	_interface.SetExitCommand("Exit");
	_interface.SetInterface(new SpreadsheetsInterface());
	_interface.Run();
	return EXIT_SUCCESS;
}