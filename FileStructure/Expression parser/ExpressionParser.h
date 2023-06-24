#pragma once
#include "Expression.h"


/// <summary>
/// A class which contains functions related to parsing a basic mathematical expression into a structure that can be evaluated
/// </summary>
class ExpressionParser
{
	public:
		enum struct OperationPrecedence
		{
			Addition,
			Multiplication,
			Exponentiation,
			Brackets
		};

	public:
		/// <summary>
		/// Splits the given expression to subexpression based on the provided operator precedence
		/// </summary>
		/// <param name="input"> The expression string</param>
		/// <param name="operations"> The vector that will store all the operators with the given precedence in order of appearance</param>
		/// <param name="precedence">The precedence to be split the string on</param>
		/// <returns>A vector containing the subexpressions seperated by the operators with the desired precedence </returns>
		static Vector<String> OperationSplit(const String& input, Vector<char>& operations, OperationPrecedence precedence);

		/// <summary>
		/// Splits the given expression to subexpressions based on any valid operation
		/// </summary>
		/// <param name="input"> The expression string</param>
		/// <param name="operations"> The vector that will store the operators in order of appearance</param>
		/// <param name="precedences">The vector that will store the precedence of the operator vector</param>
		/// <returns>A vector containing the subexpressions seperated by any operator</returns>
		static Vector<String> OperationSplit(const String& input, Vector<char>& operations, Vector<OperationPrecedence>& precedences);

		/// <summary>
		/// A fucntion that checks if a symbol is a valid operator
		/// </summary>
		static bool IsOperation(char symbol);

		/// <summary>
		/// A function that determines the operator precedence of a given operator
		/// </summary>
		/// <returns>An enum struct of the operator precedence</returns>
		static OperationPrecedence GetOperatorPrecedence(char _operator);

		/// <summary>
		/// A function that parses a given string to polymorphic object structure which can be then easily evaluated
		/// </summary>
		/// <returns>A pointer to an expression object</returns>
		static Expression* ParseExpression(const String& expression);
};

