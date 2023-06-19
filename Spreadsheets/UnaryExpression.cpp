#include "UnaryExpression.h"

UnaryExpression::UnaryExpression(char operation, Expression* operand)
{
	this->operand = operand->Clone();
	this->operation = UnaryOperation(operation);
}

UnaryExpression::UnaryExpression(Expression* operand)
{
	this->operand = operand->Clone();
	this->operation = UnaryOperation();
}

UnaryExpression::UnaryExpression(const UnaryExpression& unaryExpression)
{
	operand = unaryExpression.operand->Clone();
	operation = unaryExpression.operation;
}

ExpressionResult* UnaryExpression::Evaluate() const
{
	return operation(operand->Evaluate());
}

Expression* UnaryExpression::Clone() const
{
	return new UnaryExpression(*this);
}

UnaryExpression::~UnaryExpression()
{
	delete operand;
}
