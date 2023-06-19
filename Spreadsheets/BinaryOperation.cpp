#include "BinaryOperation.h"

BinaryOperation::BinaryOperation(char _operator) : _operator(_operator)
{

}

ExpressionResult* BinaryOperation::operator()(ExpressionResult* left, ExpressionResult* right) const
{
	switch (_operator)
	{
		case '\0':
			return nullptr;
			break;
		case '+':
			return left->Add(right);
			break;
		case '-':
			return left->Add(right->Minus());
			break;
		case '/':
			return left->Multiply(right);
			break;
		case '*':
			return left->Multiply(right);
			break;
		case '^':
			return left->Power(right);
			break;
		default:
			throw std::runtime_error("Invalid operator!!!");
			break;
	}
}
