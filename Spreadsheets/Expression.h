#pragma once
#include "String.h"
#include "ExpressionResult.h"

class Expression
{
	public:
		virtual ExpressionResult* Evaluate() const = 0;
		virtual Expression* Clone() const = 0;
		virtual ~Expression() = default;
};

