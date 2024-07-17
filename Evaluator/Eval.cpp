#include "Eval.h"
#include "include/Evaluator.hpp"

/*
#include "include/utility.hpp"
#include "include/common.h"
#include "include/Parser.hpp"
#include "include/Expression.hpp"
#include "include/Precedence.hpp"
#include "include/SyntaxTree.hpp"
*/
namespace evl = evaluator;

namespace {
evl::Evaluator expreval;
}

namespace evaluator {
Operand eval(std::string_view expression)
{
    expreval.feed(static_cast<std::string>(expression));
    return expreval.evaluate();
}
}
