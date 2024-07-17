#include "Precedence.hpp"

using namespace evaluator;
using namespace operations;

const EVALUATOR_API std::map<Precedence::Operator, OperatorPrecedence> Precedence::precedenceTable = {
	{ BinaryOPS::SUBTRACTION, SUB },
	{ BinaryOPS::ADDITION, ADD },
	{ BinaryOPS::DIVISION, DIV },
	{ BinaryOPS::MULTIPLICATION, MUL },
	{ BinaryOPS::EXPONENTIATION, EXP },
    { BinaryOPS::MODULATION, MOD },
    { UnaryOPS::NEGATION, UNR },
    { UnaryOPS::FACTORIAL, UNR }
};
