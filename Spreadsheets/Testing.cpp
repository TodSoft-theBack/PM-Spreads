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

	Expression* expr = ExpressionParser::ParseExpression("-5 + 10 * 2");
	ExpressionResult* result = expr->Evaluate();
	std::cout << result->GetResult();
	
	return EXIT_SUCCESS;
}