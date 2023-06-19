#include <iostream>
#include "Application.h"
#include "SpreadsheetsInterface.h"
#include "ExpressionParser.h"

int main()
{
	Application app;
	app.SetApplicationName("PM Spreads");
	app.SetExitCommand("Exit");
	app.SetInterface(new SpreadsheetsInterface());
	app.Run();

	return EXIT_SUCCESS;
}