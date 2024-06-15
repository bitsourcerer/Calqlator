#include "pch.h"
#include <algorithm>
#include <numeric>
#include <stack>
#include <list>

#include "SyntaxTree.hpp"
#include "Parser.hpp"

/*
 TODO: enable multithreading support {Start from Token Queue and replace it with ThreadSafeQueue, Producer and Consumer}
*/

using namespace evaluator;
using namespace evaluator::operations;

SyntaxTree::SyntaxTree() : root(nullptr)
{
}

SyntaxTree::SyntaxTree(std::string_view expression) : SyntaxTree()
{
	build(expression);
}

evaluator::SyntaxTree::SyntaxTree(const std::queue<Token> &tokens)
{
	build(tokens);
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
		if (std::count_if(token.cbegin(), token.cend(), std::isdigit))
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

SyntaxTree & evaluator::SyntaxTree::build(const std::queue<Token>& tokens)
{
	auto toks(tokens);
	std::list<Token> ltok(toks.size());
	for (auto &t : ltok)
	{
		t = toks.front();
		toks.pop();
	}

	std::stack<std::unique_ptr<Expression>> expressions;
	while (!ltok.empty())
	{
		auto current = ltok.front();
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
		ltok.pop_front();
	}

	root = std::move(expressions.top()); expressions.pop();
	return *this;
}

SyntaxTree& SyntaxTree::buildFromOldTokens(const std::queue<OldToken> &tokens)
{
	constexpr auto Invalid = std::numeric_limits<Operand>::quiet_NaN();
	std::queue<OldToken> tokenStrm(tokens);

	// only if expression is container of Tokens it can be easier to parse
	std::stack<std::unique_ptr<Expression>> expressions;
	for (OldToken current = tokenStrm.front(); !tokenStrm.empty();)
	{
		auto &value = current.getValue();
		switch (current.getType())
		{
		case OldToken::Type::OPERAND:
		{
			auto num = std::any_cast<Operand>(value);
			expressions.push(std::make_unique<Number>(num));
		} break;
		case OldToken::Type::OPERATION:
			/* TODO: unify TokenType OPERATOR and FUNCTION into OPERATION */
		{
			auto oper = std::any_cast<OldOperation>(value);
			std::unique_ptr<Expression> expr;
			switch (oper.type)
			{
			case OldOperation::FUNCTION:
			{
				expr = std::make_unique<Function>(std::move(expressions.top()), oper.f);
				expressions.pop();
			} break;
			case OldOperation::BINARY:
			{
				auto right = std::move(expressions.top()); expressions.pop();
				auto left = std::move(expressions.top()); expressions.pop();

				expr = std::make_unique<Binary>(std::move(left), std::move(right), oper.b);
			} break;
			case OldOperation::UNARY:
			{
				expr = std::make_unique<Unary>(888.888, oper.u); // TODO
			} break;
			default:
				break;
			}
			expressions.push(std::move(expr));
		} break;
		default:
			break;
		}
		tokenStrm.pop();
		if (!tokenStrm.empty()) current = tokenStrm.front();
		// current = tokenStrm.front();
	}
	assert(!expressions.empty());
	root = std::move(expressions.top()); expressions.pop();

	return *this;
}

Result SyntaxTree::evaluate() const
{
	return root->evaluate();
}

//void SyntaxTree::assign(NodePtr node)
//{
//	if(!root) root = node;
//	decltype(root) n;
//	for (n = root; n->next; n = n->next);
//	n = node;
//}

//void SyntaxTree::assign(std::unique_ptr<Expression> expression)
//{
//	assign(insert(std::move(expression)));
//}

//SyntaxTree::NodePtr SyntaxTree::insert(std::unique_ptr<Expression> expression)
//{
//	// if (!root) { root = std::move(node); return; }
//	return std::make_unique<Expression>(std::move(expression));
//}
