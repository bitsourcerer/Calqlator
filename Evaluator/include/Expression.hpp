#pragma once

#include "pch.h"
#include "common.h"
// #define interface struct

namespace evaluator
{
	__interface Expression
	{
		virtual Result evaluate(void) const = 0;
	};

	class Number : public Expression
	{
	public:
		Number(double);
		Result evaluate() const noexcept override;
	private:
		Operand value;
	};

	class Unary : public Expression
	{
	public:
		Unary(Number, char);
		Unary(Number, operations::UnaryOPS);
		Result evaluate() const noexcept override;

	private:
		Number value;
		operations::UnaryOPS operation;
	};

	class Binary : public Expression
	{
		using VExpression = std::unique_ptr<Expression>;
	public:
		Binary(VExpression, VExpression, operations::BinaryOPS);
		Result evaluate() const override;

	private:
		VExpression left, right;
		operations::BinaryOPS operation;
	};

	class Function : public Expression
	{
	public:
		Function(std::unique_ptr<Expression>, operations::Functions);
		Result evaluate() const override;

	private:
		std::unique_ptr<Expression> value;
		operations::Functions function;
	};

	// template <OperationType opt>

	/*template <> struct Token<OperationType::UNARY>
	{
		char op;
		operand_t operand;
	};*/

	/*template <> struct Token<OperationType::BINARY>
	{
		char op;
		operand_t lhs, rhs;
	};*/
}