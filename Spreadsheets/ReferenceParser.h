#pragma once
#include "String.h"
#include "Cell.h"
class ReferenceParser
{
	public:
		static String SubstituteTalbeReferences(const String& value, const Vector<Vector<UniquePtr<Cell>>>& referenceTable);
};