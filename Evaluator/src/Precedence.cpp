#include "pch.h"
#include "Precedence.hpp"

using namespace evaluator;
using namespace operations;

const EVALUATOR_API std::map<BinaryOPS, OperatorPrecedence> Precedence::precedence = {
	{ BinaryOPS::SUBTRACTION, SUB },
	{ BinaryOPS::ADDITION, ADD },
	{ BinaryOPS::DIVISION, DIV },
	{ BinaryOPS::MULTIPLICATION, MUL },
	{ BinaryOPS::EXPONENTIATION, EXP },
	{ BinaryOPS::MODULATION, MOD }
};