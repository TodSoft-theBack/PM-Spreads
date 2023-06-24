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
	bool isInSubexpression = false, hasOperations = false;
	size_t length = input.Length();

	for (const char currentChar : input)
	{
		if (currentChar == ' ')
			continue;

		if (currentChar == '(')
			isInSubexpression = true;

		if (currentChar == ')')
			isInSubexpression = false;

		if (IsOperation(currentChar) && GetOperatorPrecedence(currentChar) == precedence)
		{
			if (isInSubexpression)
			{
				string.PushBack(currentChar);
				continue;
			}
			operations.PushBack(currentChar);
			hasOperations = true;
			result.PushBack(String::Trim(string));
			string.Clear();
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
			continue;
		}

		if (IsOperation(currentChar))
		{
			if (isInSubexpression)
			{
				string.PushBack(currentChar);
				continue;
			}
			operations.PushBack(currentChar);
			precedences.PushBack(GetOperatorPrecedence(currentChar));
			hasOperations = true;
			result.PushBack(String::Trim(string));
			string.Clear();
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
		case 'r': // r stands for radical or root 3 r 8 means the 3rd root of 8 its here for future implementations
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

	if (expression.First() == '(' && expression.Last() == ')')
		return ParseExpression(expression.Substring(1, expression.Length() - 2));

	Vector<char> operations;

	//check for addition precedence
	Vector<String> result = OperationSplit(expression, operations, OperationPrecedence::Addition);
	
	if (result.Count() == 2)
		return new BinaryExpression(operations[0], ParseExpression(result[0]), ParseExpression(result[1]));

	//check for multiplication precedence
	if (result.Count() == 1)
		result = OperationSplit(expression, operations, OperationPrecedence::Multiplication);

	if (result.Count() == 2)
		return new BinaryExpression(operations[0], ParseExpression(result[0]), ParseExpression(result[1]));

	//check for exponentiation precedence
	if (result.Count() == 1)
		result = OperationSplit(expression, operations, OperationPrecedence::Exponentiation);

	if (result.Count() == 2)
		return new BinaryExpression(operations[0], ParseExpression(result[0]), ParseExpression(result[1]));

	//check for brackets

	Expression* output = nullptr;
	bool isInitialised = false;
	size_t operationsCount = operations.Count();

	for (size_t i = 0; i < operationsCount; i++)
	{
		if (!isInitialised)
		{
			String left = result[i], right = result[i + 1];
			if (right.IsEmpty())
				throw std::runtime_error("Invalid Expression");
			if (left.IsEmpty())
				output = new UnaryExpression(operations[i], ParseExpression(right));
			else
				output = new BinaryExpression(operations[i], ParseExpression(left), ParseExpression(right));
			isInitialised = true;
		}
		else
			output = new BinaryExpression(operations[i], output, ParseExpression(result[i + 1]));	}

	return output;
}
