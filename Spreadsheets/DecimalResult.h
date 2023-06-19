#pragma once
#include "ExpressionResult.h"
#include "String.h"

class DecimalResult : public ExpressionResult
{
	private:
		double value = 0;

	public:
		DecimalResult(double value);
		double Value() const;
		String Result() const override;
		ExpressionResult* Plus();
		ExpressionResult* Minus();
		
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

