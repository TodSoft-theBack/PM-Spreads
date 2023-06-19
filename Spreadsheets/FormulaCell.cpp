#include "FormulaCell.h"
#include "ExpressionParser.h"

FormulaCell::FormulaCell(const String& string) : value(string){}

Cell* FormulaCell::Clone() const
{
	return new FormulaCell(*this);
}

String FormulaCell::ToString(const Vector<Vector<UniquePtr<Cell>>>& reference) const
{
	String replacedReferences;
	ExpressionResult* result = ExpressionParser::ParseExpression(replacedReferences.GetStringView())->Evaluate();
	return String();
}
