#include "ExpressionParser.h"
#include "BinaryExpression.h"
#include "UnaryExpression.h"
#include "ValueExpression.h"


bool IsBracket(char symbol)
{
	return symbol == '(' || symbol == ')';
}

bool IsSpace(char symbol)
{
	return symbol == ' ';
}

bool IsOperation(char symbol)
{
	return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^';
}

Vector<String> ExpressionParser::OperationSplit
(
	const String& input, 
	Vector<size_t>& operationIndecies, 
	Vector<char>& operations, 
	Vector<OperationPrecedence>& precedence
)
{
	Vector<String> result;
	Vector<char> string;
	Vector<char> subexpression;
	bool isInSubexpression = false;
	size_t length = input.Length();

	int delimIndex = -1;
	for (size_t i = 0; i < length; i++)
	{

		char currentChar = input[i];
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
			operationIndecies.PushBack(i);
			operations.PushBack(currentChar);
			precedence.PushBack(GetOperatorPrecedence(currentChar));
			delimIndex = i;
			result.PushBack(String::Trim(string));
			string = std::move(Vector<char>());
			continue;
		}
		string.PushBack(currentChar);
	}
	if (delimIndex == -1)
	{
		result.PushBack(input);
		return result;
	}
	if (!string.IsEmpty())
		result.PushBack(String::Trim(string));
	return result;
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

	Vector<OperationPrecedence> precedences;
	Vector<char> operations;
	Vector<size_t> indecies;

	Vector<String> result = OperationSplit(expression, indecies, operations, precedences);

	std::cout << result << std::endl;
	std::cout << operations << std::endl;
	std::cout << indecies << std::endl;

	size_t minPrecedenceIndex = 0;
	for (size_t i = 1; i < operations.Count(); i++)
		if (precedences[i] < precedences[minPrecedenceIndex])
			minPrecedenceIndex = i;

	String leftOperand = result[minPrecedenceIndex], rightOperand = result[minPrecedenceIndex + 1];
	if (leftOperand.IsEmpty())
		return new UnaryExpression(operations[minPrecedenceIndex], ParseExpression(rightOperand));
	else
		return new BinaryExpression(operations[minPrecedenceIndex], ParseExpression(leftOperand), ParseExpression(rightOperand));
}
