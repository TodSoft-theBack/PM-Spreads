#include "ValueExpression.h"
#include "IntegerResult.h"
#include "DecimalResult.h"

ValueExpression::ValueExpression()
{
	SetValue("");
}

ValueExpression::ValueExpression(const String& value)
{
	SetValue(value);
}

ExpressionResult* ValueExpression::Evaluate() const
{
	if (value.IsInteger())
		return new IntegerResult(value.IntegerParse());
	else if (value.IsDecimal())
		return new DecimalResult(value.DecimalParse());
	return new IntegerResult(0);
}

Expression* ValueExpression::Clone() const
{
	return new ValueExpression(*this);
}

void ValueExpression::SetValue(const String& string)
{
	this->value = string;
}
