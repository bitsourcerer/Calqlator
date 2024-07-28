#include "Precedence.hpp"

using namespace evaluator;
using namespace operations;

std::greater_equal<OperatorPrecedence> Precedence::comparator;

const EVALUATOR_API std::map<Precedence::Operator, OperatorPrecedence> Precedence::precedenceTable = {
	{ BinaryOPS::SUBTRACTION, SUB },
	{ BinaryOPS::ADDITION, ADD },
	{ BinaryOPS::DIVISION, DIV },
	{ BinaryOPS::MULTIPLICATION, MUL },
	{ BinaryOPS::EXPONENTIATION, EXP },
    { BinaryOPS::MODULATION, MOD },
    { UnaryOPS::NEGATION, UNR },
    { UnaryOPS::FACTORIAL, UNR },
    { Functions::SIN, FUN },
    { Functions::COS, FUN },
    { Functions::TAN, FUN },
    { Functions::SQRT, FUN },
    { Functions::LOG2, FUN },
    { Functions::LOG10, FUN },
    { Functions::LOGN, FUN }
};
