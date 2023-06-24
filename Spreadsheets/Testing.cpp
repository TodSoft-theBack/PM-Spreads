#include <iostream>
#include "Application.h"
#include "SpreadsheetsInterface.h"
#include "ExpressionParser.h"
#include "BinaryExpression.h"
#include "UnaryExpression.h"
#include "ValueExpression.h"


int main()
{
	/*Application app;
	app.SetApplicationName("PM Spreads");
	app.SetExitCommand("Exit");
	app.SetInterface(new SpreadsheetsInterface());
	app.Run();*/

	String expression;
	std::cout << "Enter math expression: ";
	ReadLine(std::cin, expression);
	while (expression != "Exit")
	{
		Expression* expr = ExpressionParser::ParseExpression(expression);
		ExpressionResult* result = expr->Evaluate();
		std::cout << result->GetResult() << std::endl;
		std::cout << "Enter math expression: ";
		ReadLine(std::cin, expression);
	}
	
	return EXIT_SUCCESS;
}