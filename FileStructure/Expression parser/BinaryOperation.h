#pragma once
#include <iostream>
#include "ExpressionResult.h"

class BinaryOperation
{
		
		char _operator = '\0';
	public:
		BinaryOperation() = default;
		BinaryOperation(char _operator);
		char Operator() const;
		ExpressionResult* operator()(ExpressionResult* left, ExpressionResult* right) const;
};

