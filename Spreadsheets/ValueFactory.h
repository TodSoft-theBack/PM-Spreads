#pragma once
#include "String.h"
#include "Value.h"

class ValueFactory
{
	public:
		static ValueExpression* CreateValue(const String& string);
};

