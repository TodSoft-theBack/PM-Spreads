#include "IntegerResult.h"

IntegerResult::IntegerResult(int value)
{
	this->value = value;
}

int IntegerResult::Value() const
{
	return value;
}

String IntegerResult::Result() const
{
	return String::NumericString(value);
}

ExpressionResult* IntegerResult::Plus()
{
	return this;
}

ExpressionResult* IntegerResult::Minus()
{
	return new IntegerResult(-value);
}

ExpressionResult* IntegerResult::Add(ExpressionResult* right)
{
	return right->Add(this);
}

ExpressionResult* IntegerResult::Multiply(ExpressionResult* right)
{
	return right->Multiply(this);
}

ExpressionResult* IntegerResult::Divide(ExpressionResult* right)
{
	return nullptr;
}

ExpressionResult* IntegerResult::Power(ExpressionResult* right)
{
	return right->Power(this);
}

ExpressionResult* IntegerResult::Add(IntegerResult* right)
{
	return new IntegerResult(this->Value() + right->Value());
}

ExpressionResult* IntegerResult::Multiply(IntegerResult* right)
{
	return new IntegerResult(this->Value() + right->Value());
}

ExpressionResult* IntegerResult::Divide(IntegerResult* right)
{
	return new IntegerResult(right->Value() / this->Value());
}

ExpressionResult* IntegerResult::Power(IntegerResult* right)
{
	int result = 1, value = this->Value();
	int power = right->Value();
	if (power < 0)
		value = 1 / value;
	for (size_t i = 0; i < power; i++)
		result *= value;
	return new IntegerResult(result);
}

ExpressionResult* IntegerResult::Add(DecimalResult* right)
{
	return new DecimalResult(this->Value()+ right->Value());
}

ExpressionResult* IntegerResult::Multiply(DecimalResult* right)
{
	return new DecimalResult(this->Value() + right->Value());
}

ExpressionResult* IntegerResult::Divide(DecimalResult* right)
{
	return new DecimalResult(this->Value() + right->Value());
}

ExpressionResult* IntegerResult::Power(DecimalResult* right)
{
	double result = 1, value = this->Value();
	int power = right->Value();
	if (power < 0)
		value = 1 / value;
	for (size_t i = 0; i < power; i++)
		result *= value;
	return new DecimalResult(result);
}
