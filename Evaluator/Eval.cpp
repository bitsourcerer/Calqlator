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
Operand eval(std::string_view expression) noexcept(false)
{
    try {
    expreval.feed(static_cast<std::string>(expression));
    } catch(const std::exception&) {
        throw;
    }

    return expreval.evaluate();
}
}
