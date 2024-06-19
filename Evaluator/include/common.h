#pragma once

#include "API.h"
#include "utility.hpp"
#include "framework.h"

// All standard includes : BEGIN
#include <functional>
#include <memory>
#include <exception>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <map>
#include <cctype>
#include <numeric>
#include <algorithm>
#include <string_view>
#include <variant>
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
	class nullstream_t : public std::ostringstream
	{
		template <typename T>
        friend nullstream_t& operator << (nullstream_t &ns, T) { return ns; }
	} static nullstream;

#ifndef NDEBUG
	static std::ostream& dbglog = std::cout;
#else
	static std::ostream& dbglog = nullstream;
#endif // !NDEBUG

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

        enum EVALUATOR_API Symbols : OperationEnumeratorUnderlyingType
        {
            PAREN
        };

		extern EVALUATOR_API std::unordered_map<operations::BinaryOPS, std::function<Result(Operand, Operand)>> binops;
		extern EVALUATOR_API std::unordered_map<operations::UnaryOPS, std::function<Result(Operand)>> unops;
		extern EVALUATOR_API const std::map<std::string_view, Functions> funcids;
		extern EVALUATOR_API const std::unordered_map<Functions, std::function<Result(Operand)>> funcs;
	}

    using Operation = std::variant</* std::monostate, */operations::UnaryOPS, operations::BinaryOPS, operations::Functions>;
    using UnifiedToken = std::variant<Operation, operations::Symbols>;
    using Token = std::variant<Operand, Operation>;
}
