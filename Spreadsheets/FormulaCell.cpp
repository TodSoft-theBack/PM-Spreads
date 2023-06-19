#include "FormulaCell.h"
#include "ExpressionParser.h"
#include "ReferenceParser.h"

FormulaCell::FormulaCell(const String& string) : value(string){}

Cell* FormulaCell::Clone() const
{
	return new FormulaCell(*this);
}

String FormulaCell::ToString(const Vector<Vector<UniquePtr<Cell>>>& reference) const
{
	return ExpressionParser::ParseExpression
	(
		ReferenceParser::SubstituteTalbeReferences(value, reference).SubstringView(1)
	)
	->Evaluate()
	->GetResult();
}
