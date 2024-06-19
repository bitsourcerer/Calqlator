// #include <algorithm>
#include <limits>
#include <stack>
#include <list>
#include <sstream>
#include <cassert>

#include "Parser.hpp"
#include "SyntaxTree.hpp"

using namespace evaluator;
using namespace evaluator::operations;

SyntaxTree::SyntaxTree() : root(nullptr)
{
}

SyntaxTree::SyntaxTree(std::string_view expression) : SyntaxTree()
{
	build(expression);
}

/*
evaluator::SyntaxTree::SyntaxTree(const Parser::TokenQueue &tokens)
{
    build(tokens);
}*/

evaluator::SyntaxTree::SyntaxTree(Parser::TokenQueue &&tokens)
{
    build(std::move(tokens));
}

// All need heavy optimizations
SyntaxTree& SyntaxTree::build(std::string_view expression)
{
	// use parser to parse for tokens
	const std::string expr (expression);
	std::istringstream strm(expr);
	constexpr auto Invalid = std::numeric_limits<Operand>::quiet_NaN();

	// only if expression is container of Tokens it can be easier to parse
	std::stack<std::unique_ptr<Expression>> exp;
	std::string token;
	char operation = 0;
	while (strm >> token)
	{
        if (std::count_if(token.cbegin(), token.cend(), ::isdigit))
		{
			auto value = std::stod(token);
			exp.push(std::make_unique<Number>(value));
		}
		else if (auto it = std::find_if(token.cbegin(), token.cend(),
			[](char c) { return binops.find(static_cast<BinaryOPS>(c)) != binops.end(); });
			it != token.end())
		{
			operation = *it;
				auto right = std::move(exp.top()); exp.pop();
				auto left = std::move(exp.top()); exp.pop();

				exp.push(std::make_unique<Binary>(std::move(left), std::move(right), static_cast<operations::BinaryOPS>(operation)));
		}
		else if (std::isalpha(token.front()))
		{
			auto fn = token.front();
			if (operations::funcs.find(static_cast<Functions>(fn)) == funcs.end()) continue;

			auto oper = std::move(exp.top()); exp.pop();
			exp.push(std::make_unique<Function>(std::move(oper), static_cast<Functions>(fn)));
		}
		else continue;
	}
	assert(!exp.empty());
	root = std::move(exp.top()); exp.pop();

	return *this;
}

SyntaxTree& evaluator::SyntaxTree::build(Parser::TokenQueue&& tokens)
{
    // auto &&toks(std::move(tokens)); // very important

    static std::stack<std::unique_ptr<Expression>> expressions;

    while (!tokens.empty())
    {
        auto &current = tokens.front();
        std::visit([&](const auto &token) {
            if constexpr (std::is_same_v<std::decay_t<decltype(token)>, Operand>)
                expressions.push(std::make_unique<Number>(token));
            else if constexpr (std::is_same_v<std::decay_t<decltype(token)>, Operation>)
            {
                std::visit([&](const auto &operation) {
                    if constexpr (std::is_same_v<std::decay_t<decltype(operation)>, operations::BinaryOPS>)
                    {
                        auto right = std::move(expressions.top()); expressions.pop();
                        auto left = std::move(expressions.top()); expressions.pop();

                        expressions.push(std::make_unique<Binary>(std::move(left), std::move(right), operation));
                    }
                    else if constexpr (std::is_same_v<std::decay_t<decltype(operation)>, operations::UnaryOPS>)
                    {
                        expressions.push(std::make_unique<Unary>(888.888, operation));
                    }
                    else if constexpr (std::is_same_v<std::decay_t<decltype(operation)>, operations::Functions>)
                    {
                        auto operand = std::move(expressions.top()); expressions.pop();
                        expressions.push(std::make_unique<Function>(std::move(operand), operation));
                    }
                    else;
                }, token);
            }
            else return;
        }, current);
        tokens.pop();
    }

    root = std::move(expressions.top()); expressions.pop();
    return *this;
}

/*
SyntaxTree& evaluator::SyntaxTree::build(const Parser::TokenQueue& tokens)
{
    // auto toks(std::move(tokens)); // very important

    std::stack<std::unique_ptr<Expression>> expressions;
    while (!toks.empty())
    {
        auto &current = toks.front();
        std::visit([&](const auto &token) {
            if constexpr (std::is_same_v<std::decay_t<decltype(token)>, Operand>)
                expressions.push(std::make_unique<Number>(token));
            else if constexpr (std::is_same_v<std::decay_t<decltype(token)>, Operation>)
            {
                std::visit([&](const auto &operation) {
                    if constexpr (std::is_same_v<std::decay_t<decltype(operation)>, operations::BinaryOPS>)
                    {
                        auto right = std::move(expressions.top()); expressions.pop();
                        auto left = std::move(expressions.top()); expressions.pop();

                        expressions.push(std::make_unique<Binary>(std::move(left), std::move(right), operation));
                    }
                    else if constexpr (std::is_same_v<std::decay_t<decltype(operation)>, operations::UnaryOPS>)
                    {
                        expressions.push(std::make_unique<Unary>(888.888, operation));
                    }
                    else if constexpr (std::is_same_v<std::decay_t<decltype(operation)>, operations::Functions>)
                    {
                        auto operand = std::move(expressions.top()); expressions.pop();
                        expressions.push(std::make_unique<Function>(std::move(operand), operation));
                    }
                    else;
                }, token);
            }
            else return;
        }, current);
        toks.pop();
    }

    root = std::move(expressions.top()); expressions.pop();
    return *this;
}*/

Result SyntaxTree::evaluate() const
{
	return root->evaluate();
}
