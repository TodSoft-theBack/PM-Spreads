#pragma once
#include "Expression.h"
#include "UnaryOperation.h"

class UnaryExpression : public Expression
{
	protected:
		Expression* operand;
		UnaryOperation operation;

	public:
		UnaryExpression(char operation, Expression* operand);
		UnaryExpression(Expression* operand);
		UnaryExpression(const UnaryExpression& unaryExpression);
		ExpressionResult* Evaluate() const override;
		Expression* Clone() const override;
		~UnaryExpression();
};

