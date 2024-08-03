// #include <algorithm>
#include <limits>
#include <stack>
#include <list>
#include <sstream>
#include <cassert>
#include <cctype>

// #include "Parser.hpp"
#include "Tree.hpp"

using namespace evaluator;
using namespace evaluator::operations;

/*
SyntaxTree::SyntaxTree() : root(nullptr)
{
}

evaluator::SyntaxTree::SyntaxTree(const Parser::TokenQueue &tokens)
{
    build(tokens);
}*/

SyntaxTree::SyntaxTree(diag::DiagnosticsHolder &holder) : diagnostics(holder, diag::Origin::SYNTREE)
{
}

/*
evaluator::SyntaxTree::SyntaxTree(Parser::TokenQueue &&tokens)
{
    build(std::move(tokens));
}*/

// All need heavy optimizations
SyntaxTree& evaluator::SyntaxTree::build(Parser::TokenQueue&& tokens)
{
    using except::missing_operand;
    // auto &&toks(std::move(tokens)); // very important

    static Parser::VecStack<std::unique_ptr<Expression>> expressions;
    // static auto check_valid = std::bind(&SyntaxTree::validate_operands, this, std::cref(expressions), std::placeholders::_1);

    while (!tokens.empty())
    {
        auto &current = tokens.front();
        auto sz = expressions.size();
        std::visit([&](const auto &token) {
            using T = std::decay_t<decltype(token)>;
            if constexpr (std::is_same_v<T, Operand>)
                expressions.push(std::make_unique<Number>(token));
            else if constexpr (std::is_same_v<T, Operation>)
            {
                // could also use std::holds_alternative
                std::visit([&](const auto &operation) {
                    using O = std::decay_t<decltype(operation)>;
                    if constexpr (std::is_same_v<O, operations::BinaryOPS>)
                    {
                        validate_operands(sz, missing_operand::BINARY);
                        auto right = std::move(expressions.top()); expressions.pop();
                        auto left = std::move(expressions.top()); expressions.pop();

                        expressions.push(std::make_unique<Binary>(std::move(left), std::move(right), operation));
                    }
                    else if constexpr (std::is_same_v<O, operations::UnaryOPS>)
                    {
                        validate_operands(sz, missing_operand::UNARY);
                        auto operand = std::move(expressions.top()); expressions.pop();
                        expressions.push(std::make_unique<Unary>(std::move(operand), operation));
                    }
                    else if constexpr (std::is_same_v<O, operations::Functions>)
                    {
                        validate_operands(sz, missing_operand::FUNCTION);
                        auto operand = std::move(expressions.top()); expressions.pop();
                        expressions.push(std::make_unique<Function>(std::move(operand), operation));
                    }
                    else {};
                }, token);
            }
            else return;
        }, current);
        tokens.pop();
    }

    if(expressions.empty())
        throw except::evaluate_error("Expression Tree is Empty!");

    root = std::move(expressions.top()); expressions.pop();
    return *this;
}

void SyntaxTree::set(Parser::TokenQueue &&tokens)
{
    this->tokens = std::move(tokens);
}

Expression* SyntaxTree::getTree() const
{
    return root.get(); // temporary workaround
}

Result SyntaxTree::evaluate() const
{
    if(!root) return 0;
	return root->evaluate();
}
