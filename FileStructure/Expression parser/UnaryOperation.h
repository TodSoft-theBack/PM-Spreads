#pragma once
#include <iostream>
#include "ExpressionResult.h"

class UnaryOperation
{
		char _operator = 'v';
	public:
		UnaryOperation() = default;
		UnaryOperation(char _operator);
		char Operator() const;
		ExpressionResult* operator()(ExpressionResult* operand) const;
};

