#include "common.h"
#include "utility.hpp"
#include <cmath>

using namespace evaluator;
using namespace evaluator::operations;

Result Factorial(Operand op) noexcept
{
    if(op == 0) return 1;
    return op * Factorial(op - 1);
}

std::unordered_map<BinaryOPS, std::function<Result(Operand, Operand)>> operations::binops = {
	{ BinaryOPS::SUBTRACTION, std::minus<operand_t>() },
	{ BinaryOPS::ADDITION, std::plus<operand_t>() },
	{ BinaryOPS::MULTIPLICATION, std::multiplies<operand_t>() },
	{ BinaryOPS::DIVISION, std::divides<operand_t>() },
	{ BinaryOPS::EXPONENTIATION, std::pow<operand_t, operand_t> },
	{ BinaryOPS::MODULATION, std::fmod<operand_t, operand_t> }, // std::modulus<operand_t>()
	{ BinaryOPS::UNSPECIFIED, nullptr }
};

std::unordered_map<UnaryOPS, std::function<Result(Operand)>> operations::unops = {
    { UnaryOPS::NEGATION, std::negate<operand_t>() },
    { UnaryOPS::FACTORIAL, Factorial }
};

const std::unordered_map<operations::Functions, std::function<Result(Operand)>> operations::funcs
{
	{ Functions::SIN , [](Operand op) -> Result { return std::sin(util::ConvertDegToRad(op)); } },
	{ Functions::COS , [](Operand op) -> Result { return std::cos(util::ConvertDegToRad(op)); } },
	{ Functions::TAN , [](Operand op) -> Result { return std::tan(util::ConvertDegToRad(op)); } },
	{ Functions::SQRT , [](Operand op) -> Result { return std::sqrt(op); } },
    { Functions::SQRT , [](Operand op) -> Result { return std::log(op); } },
	{ Functions::LOG10 , [](Operand op) -> Result { return std::log10(op); } },
	{ Functions::LOG2, [](Operand op) -> Result { return std::log2(op); } }
};

const std::map<std::string_view, Functions> operations::funcids
{
	{ "sin", Functions::SIN },
	{ "cos", Functions::COS },
	{ "tan", Functions::TAN },
	{ "sqrt", Functions::SQRT },
	{ "logten", Functions::LOG10 },
    { "logtwo", Functions::LOG2 },
    { "logn", Functions::LOGN }
};

// extern std::ostream& dbglog;
