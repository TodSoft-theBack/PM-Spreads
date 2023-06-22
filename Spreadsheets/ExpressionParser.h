#pragma once
#include "Expression.h"

bool IsBracket(char symbol);
bool IsSpace(char symbol);
bool IsOperation(char symbol);


class ExpressionParser
{
	public:
		enum struct OperationPrecedence 
		{
			Addition,
			Multiplication,
			Exponentiation,
			Tetration
		};
		static Vector<String> OperationSplit(const String& input, Vector<size_t>& operationIndecies, Vector<char>& operations, Vector<OperationPrecedence>& precedence);
		static OperationPrecedence GetOperatorPrecedence(char _operator);
		static Expression* ParseExpression(const String& expression);
};

