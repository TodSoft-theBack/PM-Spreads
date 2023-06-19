#include "ExpressionParser.h"
#include "BinaryExpression.h"
#include "UnaryExpression.h"
#include "ValueFactory.h"


bool IsOperation(char symbol)
{
	return symbol == '+' || symbol == '-' ||symbol == '*' || symbol=='/' || symbol == '^';
}

Expression* ExpressionParser::ParseExpression(const String::StringView& expression)
{
	size_t length = expression.length;
	Vector<char> subExpression;
	Vector<char> operand;
	bool hasDecimal = false, IsInsubExpression = false;
	if (expression.length == 0)
		return new UnaryExpression(ValueFactory::CreateValue(String(operand)));

	for (size_t i = 0; i < length; i++)
	{
		
		if (expression[i] == '(')
		{
			IsInsubExpression = true;
			continue;
		}
		if (expression[i] == ')')
		{
			IsInsubExpression = false;
			continue;
		}

		if (IsInsubExpression)
		{
			subExpression.PushBack(expression[i]);
			continue;
		}

		if (String::IsDigit(expression[i]))
			operand.PushBack(expression[i]);
		else if (!hasDecimal && (expression[i] == '.' || expression[i] == ','))
		{
			operand.PushBack(expression[i]);
			hasDecimal = true;
		}
		else if (IsOperation(expression[i]))
		{
			if (subExpression.Count() != 0)
				return new BinaryExpression
				(
					expression[i],
					ParseExpression(String(subExpression).GetStringView()),
					ParseExpression(expression.SubstringView(i + 1)
					));

			if (operand.Count() == 0)
			{
				for (size_t j = i + 1; j < length; j++)
				{
					if (String::IsDigit(expression[j]) || expression[j] == '.' || expression[j] == ',' || expression[j] == ' ')
						continue;
					if (expression[j] == '(')
						return new UnaryExpression
						(
							expression[i],
							ParseExpression(expression.SubstringView(i + 1, j - i))
						);
					else
						return new BinaryExpression
						(
							expression[j],
							new UnaryExpression(expression[i], ParseExpression(expression.SubstringView(i + 1, j - i - 1))),
							ParseExpression(expression.SubstringView(j + 1))
						);
				}
			}
				
			return new BinaryExpression
			(
				expression[i], 
				ParseExpression(String(operand).SubstringView(0, i)),
				ParseExpression(expression.SubstringView(i+1))
			);
		}
	}
}
