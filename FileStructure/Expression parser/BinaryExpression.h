#pragma once
#include "Expression.h"
#include "BinaryOperation.h"


class BinaryExpression : public Expression
{
	protected:
		BinaryOperation operation;
		Expression* leftOperand = nullptr;
		Expression* rightOperand = nullptr;
	public:
		BinaryExpression(char operation, Expression* leftOperand, Expression* rightOperand);
		BinaryExpression(const BinaryExpression& binaryExpression);
		ExpressionResult* Evaluate() const override;
		Expression* Clone() const override;
		~BinaryExpression();
};

