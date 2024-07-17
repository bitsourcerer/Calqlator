#ifndef EVAL_H
#define EVAL_H

#include <string_view>
#include "include/utility.hpp"

namespace evaluator {
Operand eval(std::string_view expression);
}

// namespace evl = evaluator;
// namespace ops = evaluator::operations;

#endif // EVAL_H
