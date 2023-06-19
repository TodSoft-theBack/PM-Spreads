#pragma once
#include "Expression.h"


class ExpressionParser
{
	public:
		static Expression* ParseExpression(const String::StringView& expression);
};

