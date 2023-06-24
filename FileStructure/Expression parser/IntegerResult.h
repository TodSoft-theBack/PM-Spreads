#pragma once
#include "ExpressionResult.h"
#include "DecimalResult.h"
#include "String.h"
class DecimalResult;

class IntegerResult : public ExpressionResult
{
	private:
		int value;

	public:

		IntegerResult(int value);
		int Value() const;
		String GetResult() const override;

		ExpressionResult* Plus() override;
		ExpressionResult* Minus() override;

		ExpressionResult* Add(ExpressionResult* right) override;
		ExpressionResult* Multiply(ExpressionResult* right) override;
		ExpressionResult* Divide(ExpressionResult* right) override;
		ExpressionResult* Power(ExpressionResult* right) override;

		ExpressionResult* Add(IntegerResult* right) override;
		ExpressionResult* Multiply(IntegerResult* right) override;
		ExpressionResult* Divide(IntegerResult* right) override;
		ExpressionResult* Power(IntegerResult* right) override;

		ExpressionResult* Add(DecimalResult* right) override;
		ExpressionResult* Multiply(DecimalResult* right) override;
		ExpressionResult* Divide(DecimalResult* right) override;
		ExpressionResult* Power(DecimalResult* right) override;
};

