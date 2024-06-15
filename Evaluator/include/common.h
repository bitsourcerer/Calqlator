#pragma once

#include "pch.h"
#include "API.h"
#include "utility.hpp"
#include <variant>

#ifndef NDEBUG
#define DEBUG true
#else
#define DEBUG false
#endif // _DEBUG

namespace {
constexpr const static bool debug = DEBUG;
}

#ifndef interface
#define interface struct
#define ABSTRACT 0
#endif

#define MULTITHREAD
#undef MULTITHREAD

namespace evaluator
{
	class nullstream_t : public std::ostringstream
	{
		template <typename T>
		friend nullstream_t& operator << (nullstream_t&, T) { }
	} static nullstream;

#ifndef NDEBUG
	static std::ostream& dbglog = std::cout;
#else
	static std::ostream& dbglog = nullstream;
#endif // !NDEBUG

	//enum /* class */ BinaryOperator : char
	//{
	//	NEGATION = '-',
	//	SUBTRACTION = '-',
	//	ADDITION = '+',
	//	MULTIPLICATION = '*',
	//	DIVISION = '/',
	//	EXPONENTIATION = '^',
	//	MODULATION = '%',
	//	UNSPECIFIED = 'x'
	//};

	namespace operations
	{
		using OperationEnumeratorUnderlyingType = char;

		enum EVALUATOR_API BinaryOPS : OperationEnumeratorUnderlyingType
		{
			SUBTRACTION = '-',
			ADDITION = '+',
			MULTIPLICATION = '*',
			DIVISION = '/',
			EXPONENTIATION = '^',
			MODULATION = '%',
			UNSPECIFIED = 'x'
		};


		enum EVALUATOR_API UnaryOPS : OperationEnumeratorUnderlyingType
		{ 
			NEGATION = '~',
			FACTORIAL = '!'
		};

		enum EVALUATOR_API Functions : OperationEnumeratorUnderlyingType
		{
			SIN = 's',
			COS = 'c',
			TAN = 't',
			SQRT = 'r',
			LOG2 = 'l',
			LOG10 = 'L'
		};

		struct OldOperation
		{
			enum EVALUATOR_API Type : char // UNUSED
			{
				NONE, // just a number (operand)
				UNARY,
				BINARY,
				FUNCTION
			} type = Type::NONE;

			// Type type = Type::NONE;

			union
			{
				Functions f;
				BinaryOPS b;
				UnaryOPS u;
				char o; // other: unused can hold parens
			};

			OldOperation() = default;
			OldOperation(Functions func) : f(func) , type(Type::FUNCTION) { }
			OldOperation(BinaryOPS bop) : b(bop) , type(Type::BINARY) { }
			OldOperation(UnaryOPS uop) : u(uop) , type(Type::FUNCTION) { }
		};

		// std::variant<BinaryOPS, UnaryOPS> UnifiedOps;
		extern EVALUATOR_API std::unordered_map<operations::BinaryOPS, std::function<Result(Operand, Operand)>> binops;
		extern EVALUATOR_API std::unordered_map<operations::UnaryOPS, std::function<Result(Operand)>> unops;
		extern EVALUATOR_API const std::map<std::string_view, Functions> funcids;
		extern EVALUATOR_API const std::unordered_map<Functions, std::function<Result(Operand)>> funcs;
	}
	using Operation = std::variant<std::monostate, operations::UnaryOPS, operations::BinaryOPS, operations::Functions>;
	// using VariantToken = std::variant<Operand, operations::UnaryOPS, operations::BinaryOPS, operations::Functions>;
	using Token = std::variant<Operand, Operation>;
}