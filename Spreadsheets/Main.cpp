#include <iostream>
#include "Application.h"
#include "SpreadsheetsInterface.h"

int main()
{
	Application app;
	app.SetApplicationName("PM Spreads");
	app.SetExitCommand("Exit");
	app.SetInterface(new SpreadsheetsInterface());
	app.Run();
	
	return EXIT_SUCCESS;
}