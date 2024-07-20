#pragma once

#include "API.h"
#include "utility.hpp"
#include "framework.h"

// All standard includes : BEGIN
#include <functional>
#include <string>
#include <unordered_map>
#include <map>
#include <string_view>
#include <variant>
#include <iosfwd>
#include <stack>
// All standard includes : END

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


        enum class EVALUATOR_API UnaryOPS : OperationEnumeratorUnderlyingType
		{
            NEGATION = '-',
            FACTORIAL = '!'
		};

        enum class EVALUATOR_API Functions : OperationEnumeratorUnderlyingType
		{
			SIN = 's',
			COS = 'c',
			TAN = 't',
			SQRT = 'r',
			LOG2 = 'l',
			LOG10 = 'L'
        };

        enum class EVALUATOR_API Symbols : OperationEnumeratorUnderlyingType
        {
            LPAREN = '(',
            RPAREN = ')',
            COMMA = ',',
            PERIOD = '.'
        };

        extern EVALUATOR_API std::unordered_map<operations::BinaryOPS, std::function<Result(Operand, Operand)>> binops;
        extern EVALUATOR_API std::unordered_map<operations::UnaryOPS, std::function<Result(Operand)>> unops;
		extern EVALUATOR_API const std::map<std::string_view, Functions> funcids;
		extern EVALUATOR_API const std::unordered_map<Functions, std::function<Result(Operand)>> funcs;
	}

    using Operation = std::variant</* std::monostate, */operations::UnaryOPS, operations::BinaryOPS, operations::Functions>;
    using UnifiedToken = std::variant<Operation, operations::Symbols, Operand>;
    using Token = std::variant<Operand, Operation>;
}
