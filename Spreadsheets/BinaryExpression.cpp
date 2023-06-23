#include "BinaryExpression.h"

BinaryExpression::BinaryExpression(char operation, Expression* leftOperand, Expression* rightOperand)
{
	this->operation = BinaryOperation(operation);
	this->leftOperand = leftOperand->Clone();
	this->rightOperand = rightOperand->Clone();
}

BinaryExpression::BinaryExpression(const BinaryExpression& binaryExpression)
{
	operation = binaryExpression.operation;
	leftOperand = binaryExpression.leftOperand->Clone();
	leftOperand = binaryExpression.rightOperand->Clone();
}

ExpressionResult* BinaryExpression::Evaluate() const
{
	return operation(leftOperand->Evaluate(), rightOperand->Evaluate());
}

Expression* BinaryExpression::Clone() const
{
	return new BinaryExpression(operation.Operator(), leftOperand->Clone(), rightOperand->Clone());
}

BinaryExpression::~BinaryExpression()
{
	delete leftOperand;
	delete rightOperand;
}
