#pragma once
#include "IntegerResult.h"
#include "DecimalResult.h"

class ExpressionResult
{
	public:
		virtual String Result() const = 0;
		virtual ExpressionResult* Plus() = 0;
		virtual ExpressionResult* Minus() = 0;

		virtual ExpressionResult* Add(ExpressionResult* right) = 0;
		virtual ExpressionResult* Multiply(ExpressionResult* right) = 0;
		virtual ExpressionResult* Divide(ExpressionResult* right) = 0;
		virtual ExpressionResult* Power(ExpressionResult* right) = 0;

		virtual ExpressionResult* Add(IntegerResult* right) = 0;
		virtual ExpressionResult* Multiply(IntegerResult* right) = 0;
		virtual ExpressionResult* Divide(IntegerResult* right) = 0;
		virtual ExpressionResult* Power(IntegerResult* right) = 0;

		virtual ExpressionResult* Add(DecimalResult* right) = 0;
		virtual ExpressionResult* Multiply(DecimalResult* right) = 0;
		virtual ExpressionResult* Divide(DecimalResult* right) = 0;
		virtual ExpressionResult* Power(DecimalResult* right) = 0;
};

