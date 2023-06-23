#pragma once
#include "Expression.h"


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

	private:
		static Vector<String> OperationSplit(const String& input, Vector<char>& operations, OperationPrecedence precedence);
		static Vector<String> OperationSplit(const String& input, Vector<char>& operations, Vector<OperationPrecedence>& precedences);

	public:
		static bool IsBracket(char symbol);
		static bool IsSpace(char symbol);
		static bool IsOperation(char symbol);
		static OperationPrecedence GetOperatorPrecedence(char _operator);
		static Expression* ParseExpression(const String& expression);
};

