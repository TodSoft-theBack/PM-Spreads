#include "UnaryOperation.h"


UnaryOperation::UnaryOperation(char _operator) : _operator(_operator)
{

}

char UnaryOperation::Operator() const
{
	return _operator;
}

ExpressionResult* UnaryOperation::operator()(ExpressionResult* operand) const
{
	switch (_operator)
	{
		case 'v':
			return operand;
			break;
		case '+':
			return operand->Plus();
			break;
		case '-':
			return operand->Minus();
			break;
		default:
			throw std::runtime_error("Invalid operator!!!");
			break;
	}
}
