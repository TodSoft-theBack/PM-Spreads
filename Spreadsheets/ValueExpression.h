#pragma once
#include "String.h"
#include "Expression.h"

class ValueExpression : public Expression
{
	private:
		String value;

	public:
		ValueExpression(const String& value);
		ExpressionResult* Evaluate() const override;
		Expression* Clone() const override;
		void SetValue(const String& stirng);
		~ValueExpression() = default;
};

