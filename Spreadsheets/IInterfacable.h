#pragma once
#include "String.h"
#include "Vector.hpp"

class IInterfacable
{
	public:
		virtual void ExecuteCommand(const String& command, const Vector<String>& arguments) = 0;
		virtual ~IInterfacable() = default;
};

