#include "DecimalResult.h"

DecimalResult::DecimalResult(double value)
{
    this->value = value;
}

double DecimalResult::Value() const
{
    return value;
}

String DecimalResult::GetResult() const
{
    return String::NumericString(value);
}

ExpressionResult* DecimalResult::Plus()
{
    return this;
}

ExpressionResult* DecimalResult::Minus()
{
    return new DecimalResult(-value);
}

ExpressionResult* DecimalResult::Add(ExpressionResult* right)
{
    return right->Add(this);
}

ExpressionResult* DecimalResult::Multiply(ExpressionResult* right)
{
    return right->Multiply(this);
}

ExpressionResult* DecimalResult::Divide(ExpressionResult* right)
{
    return right->Divide(this);
}

ExpressionResult* DecimalResult::Power(ExpressionResult* right)
{
    return right->Power(this);
}

ExpressionResult* DecimalResult::Add(IntegerResult* right)
{
    
    return new DecimalResult(this->Value() + right->Value());
}

ExpressionResult* DecimalResult::Multiply(IntegerResult* right)
{
    return new DecimalResult(this->Value() * right->Value());
}

ExpressionResult* DecimalResult::Divide(IntegerResult* right)
{
    return new DecimalResult(right->Value() / this->Value());
}

ExpressionResult* DecimalResult::Power(IntegerResult* right)
{
    double result = 1, value = this->Value();
    int power = right->Value();
    if (power < 0)
        value = 1 / value;
    for (size_t i = 0; i < power; i++)
        result *= value;
    return new DecimalResult(result);
}

ExpressionResult* DecimalResult::Add(DecimalResult* right)
{
    return new DecimalResult(this->Value() + right->Value());
}

ExpressionResult* DecimalResult::Multiply(DecimalResult* right)
{
    return new DecimalResult(this->Value() * right->Value());
}

ExpressionResult* DecimalResult::Divide(DecimalResult* right)
{
    return new DecimalResult(right->Value() / this->Value());
}

ExpressionResult* DecimalResult::Power(DecimalResult* right)
{
    double result = 1, value = this->Value();
    int power = right->Value();
    if (power < 0)
        value = 1 / value;
    for (size_t i = 0; i < power; i++)
        result *= value;
    return new DecimalResult(result);
}
