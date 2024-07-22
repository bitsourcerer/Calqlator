#pragma once

// TODO : Switch both to long double
typedef double operand_t;
typedef double result_t;

using Operand = operand_t;
using Result = result_t;

namespace evaluator::util
{
	constexpr const double PI = 3.14159265358979323846264338327950288419716939937510;

	constexpr double ConvertDegToRad(Operand deg) { return deg * (PI / 180); }
	constexpr double ConvertRadToDeg(Operand rad) { return rad * (180 / PI); }
}

#define EMIT(msg) \
do { \
std::cerr << msg; \
} while(false)

#ifndef NDEBUG
#define DEBUG_EMIT(msg) EMIT(msg)
#else
#define DEBUG_EMIT(...)
#endif

#define ABORT(msg) EMIT(msg); std::abort()

#define SYNTAX_ERROR(msg) EMIT((std::string("Syntax Error: ") + msg))
