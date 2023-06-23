#include "ExpressionParser.h"
#include "BinaryExpression.h"
#include "UnaryExpression.h"
#include "ValueExpression.h"



Vector<String> ExpressionParser::OperationSplit
(
	const String& input,
	Vector<char>& operations,
	OperationPrecedence precedence
)
{
	Vector<String> result;
	Vector<char> string;
	Vector<char> subexpression;
	bool isInSubexpression = false, hasOperations = false;
	size_t length = input.Length();

	for (const char currentChar : input)
	{
		if (currentChar == ' ')
			continue;

		if (currentChar == '(')
		{
			isInSubexpression = true;
			continue;
		}

		if (currentChar == ')')
		{
			isInSubexpression = false;
			string = subexpression;
			subexpression.Clear();
			continue;
		}

		if (isInSubexpression)
		{
			subexpression.PushBack(currentChar);
			continue;
		}

		if (IsOperation(currentChar) && GetOperatorPrecedence(currentChar) == precedence)
		{
			operations.PushBack(currentChar);
			hasOperations = true;
			result.PushBack(String::Trim(string));
			string = std::move(Vector<char>());
			continue;
		}
		string.PushBack(currentChar);
	}
	if (!hasOperations)
	{
		result.PushBack(input);
		return result;
	}
	if (!string.IsEmpty())
		result.PushBack(String::Trim(string));
	return result;
}

Vector<String> ExpressionParser::OperationSplit
(
	const String& input, 
	Vector<char>& operations, 
	Vector<OperationPrecedence>& precedences
)
{
	Vector<String> result;
	Vector<char> string;
	Vector<char> subexpression;
	bool isInSubexpression = false, hasOperations = false;
	size_t length = input.Length();

	for (char currentChar : input)
	{
		if (currentChar == ' ')
			continue;

		if (currentChar == '(')
		{
			isInSubexpression = true;
			continue;
		}

		if (currentChar == ')')
		{
			isInSubexpression = false;
			string = subexpression;
			subexpression.Clear();
			continue;
		}

		if (isInSubexpression)
		{
			subexpression.PushBack(currentChar);
			continue;
		}

		if (IsOperation(currentChar))
		{
			operations.PushBack(currentChar);
			precedences.PushBack(GetOperatorPrecedence(currentChar));
			hasOperations = true;
			result.PushBack(String::Trim(string));
			string = std::move(Vector<char>());
			continue;
		}
		string.PushBack(currentChar);
	}

	if (!hasOperations)
	{
		result.PushBack(input);
		return result;
	}

	if (!string.IsEmpty())
		result.PushBack(String::Trim(string));
	return result;
}

bool ExpressionParser::IsBracket(char symbol)
{
	return symbol == '(' || symbol == ')';
}

bool ExpressionParser::IsSpace(char symbol)
{
	return symbol == ' ';
}

bool ExpressionParser::IsOperation(char symbol)
{
	return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^';
}

ExpressionParser::OperationPrecedence ExpressionParser::GetOperatorPrecedence(char _operator)
{
	switch (_operator)
	{
		case '+':
		case '-':
			return OperationPrecedence::Addition;

		case '*':
		case '/':
			return OperationPrecedence::Multiplication;

		case '^':
		case 'r':
			return OperationPrecedence::Exponentiation;

		default:
			throw std::runtime_error("Invalid operator");
	}
}

Expression* ExpressionParser::ParseExpression(const String& expression)
{
	String::NumericType type = expression.CheckType();
	switch (type)
	{
		case String::NumericType::Integer:
		case String::NumericType::Decimal:
			return new ValueExpression(expression);
	}

	Vector<char> operations;

	Vector<String> result = OperationSplit(expression, operations, OperationPrecedence::Addition);

	if (result.Count() == 1)
		result = OperationSplit(expression, operations, OperationPrecedence::Multiplication);

	if (result.Count() == 1)
		result = OperationSplit(expression, operations, OperationPrecedence::Exponentiation);

	Expression* output = nullptr;

	for (size_t i = 0; i < operations.Count(); i++)
	{
		if (output == nullptr)
		{
			String left = result[i], right = result[i + 1];
			if (left.IsEmpty())
				output = new UnaryExpression(operations[i], ParseExpression(right));
			else
				output = new BinaryExpression(operations[i], ParseExpression(left), ParseExpression(right));
		}
		else
			output = new BinaryExpression(operations[i], output, ParseExpression(result[i + 1]));	}

	return output;
}
