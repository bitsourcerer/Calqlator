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
//#include <iosfwd>
#include <iostream>
#include <iomanip>
#include <stack>
// All standard includes : END

#ifndef NDEBUG
#define DEBUG true
#else
#define DEBUG false
#endif // _DEBUG

#ifndef CHAR_FLUSH
#define FLUSH_ON_NL true
#else
#define FLUSH_ON_NL false
#endif

namespace {
constexpr const static bool debug = DEBUG;
constexpr const static bool flush_on_newline = FLUSH_ON_NL;
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

        enum class BinaryOPS : OperationEnumeratorUnderlyingType
		{
			SUBTRACTION = '-',
			ADDITION = '+',
			MULTIPLICATION = '*',
			DIVISION = '/',
			EXPONENTIATION = '^',
			MODULATION = '%',
			UNSPECIFIED = 'x'
		};


        enum class UnaryOPS : OperationEnumeratorUnderlyingType
		{
            NEGATION = '-',
            FACTORIAL = '!',
            UNSPECIFIED = 'x'
		};

        enum class Functions : OperationEnumeratorUnderlyingType
		{
			SIN = 's',
			COS = 'c',
			TAN = 't',
			SQRT = 'r',
			LOG2 = 'l',
            LOG10 = 'L',
            LOGN = 'e',
            UNSPECIFIED = 'x'
        };

        enum class Symbols : OperationEnumeratorUnderlyingType
        {
            LPAREN = '(',
            RPAREN = ')',
            COMMA = ',',
            PERIOD = '.'
        };

        enum class Sentinels : OperationEnumeratorUnderlyingType
        {
            FUNC_BEG = '(', FUNC_END = ')',
            TOK_BEG = '<', TOK_END = '>' // future use
        };

        extern EVALUATOR_API std::unordered_map<operations::BinaryOPS, std::function<Result(Operand, Operand)>> binops;
        extern EVALUATOR_API std::unordered_map<operations::UnaryOPS, std::function<Result(Operand)>> unops;
		extern EVALUATOR_API const std::map<std::string_view, Functions> funcids;
		extern EVALUATOR_API const std::unordered_map<Functions, std::function<Result(Operand)>> funcs;
	}

    using Operation = std::variant</* std::monostate, */operations::UnaryOPS, operations::BinaryOPS, operations::Functions>;
    using UnifiedToken = std::variant<Operation, operations::Symbols, operations::Sentinels, Operand>;
    using Token = std::variant<Operand, Operation>;

namespace except {

class evaluator_exception : public std::exception
{
public:
    evaluator_exception(const std::string &message = "Generic Evaluator Error") : msg(message)
    {
        if constexpr (flush_on_newline)
            if(msg.find('\n', msg.length() / 2) != std::string::npos) nl = true;
    }

    const char* what() const noexcept override
    {
        if constexpr(flush_on_newline)
            if(!nl) msg.push_back('\n');

        return msg.c_str();
    }

private:
    mutable std::string msg;
    bool nl = false;
};

} // except

} // evaluator
