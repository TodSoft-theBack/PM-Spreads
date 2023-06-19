#include <iostream>
#include "Application.h"
#include "SpreadsheetsInterface.h"
#include "ExpressionParser.h"

int main()
{
	/*Application app;
	app.SetApplicationName("PM Spreads");
	app.SetExitCommand("Exit");
	app.SetInterface(new SpreadsheetsInterface());
	app.Run();*/

	Expression* expression = ExpressionParser::ParseExpression(String("-5 + 10  + (3 + 2 ^ 2)").GetStringView());
	std::cout << expression->Evaluate() << std::endl;
	return EXIT_SUCCESS;
}