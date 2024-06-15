#include "pch.h"
#include <sstream>
#include <future>

#include "Parser.hpp"
#include "StackandQueue/Stack.hpp"

using namespace evaluator;
using namespace evaluator::operations;

Parser::Parser(std::string_view exp) : input(exp)
{
}

Parser& Parser::feed(std::string_view exp)
{
	input = exp;
	// numbers.clear();
	// operations.clear();
	return *this;
}

std::string Parser::parse() const
{
	auto ret = ShuntingYard(input);
	output = ret.first;
	tokens = ret.second;
	return output;
}

const std::queue<Token>& Parser::getTokens() const
{
	// if (tokens.empty()) parse();
	parse();
	return tokens;
}

std::pair<std::string, std::queue<Token>> Parser::ShuntingYard(const std::string &expression)
{
	std::queue<Token> tokens;
	std::stack<Operation> operations;

	std::ostringstream output; // for string version
	Stack<std::underlying_type_t<operations::Functions>> ops; // for string version

	for (std::string::size_type i = 0; i != expression.length(); ++i)
	{
		const std::string::value_type current = expression.at(i);
		if (std::isspace(current)) continue;
		else if (binops.find(static_cast<BinaryOPS>(current)) != binops.end())
		{
			BinaryOPS operation = static_cast<BinaryOPS>(current);
			if (!ops.empty())
			{
				auto top = ops.top(); //o2
				while (!ops.empty() && top != '(' && Precedence::checkPrecedence((BinaryOPS)top, (BinaryOPS)current)) {
					auto o2 = ops.pop();
					output << o2 << ' ';

					tokens.push(operations.top()); operations.pop();
					top = ops.top();
				}
			}
			ops.push(current); // o1
			operations.push(operation);
		}
		else if (std::isalpha(current)) // combine all chars until they are alphabets
		{
			// lets assume the first token after any alphabet is '(' sqrt(10.0678)
			auto ite = std::find(expression.cbegin() + i, expression.cend(), ')'); // closing of function
			std::string::size_type start = expression.find_first_of("(", i+2);
			auto fn = expression.substr(i, start - i);
			auto itb = expression.cbegin() + i;

			if (operations::funcids.find(fn) == funcids.end()) continue; // not a registered function (not found in registry map

			operations.push(funcids.at(fn));
			{
				std::string whole(itb, ite); whole.push_back(')'); // for debugging purposes
				Operand value = std::stod(whole.substr(fn.length() + 1));;

				tokens.push(value);
				tokens.push(operations.top()); operations.pop();

				output << value << ' ';
				output << (char)operations::funcids.at(fn);

				i += whole.length() - 1;
			}
		}
		else if (current == '(') ops.push('(');
		else if (current == ')') // asserting whether operator stack is empty can indicate paren mismatch
		{
			decltype(ops)::value_type top;
			if (ops.empty()) continue;
			for (top = ops.pop(); top != '('; top = ops.pop())
			{
				if (ops.empty()) throw std::logic_error("Expression Mismatch");
				output << ' ' << top;
				tokens.push(operations.top()); operations.pop(); // UNLOCK
			}
		}
		else if (std::ispunct(current) && current == ','); // pop all operators from operator stack into queue (while its not left paren)
		else if (std::isdigit(current) || current == '.')
		{
			std::size_t idx = 0;
			Operand value = std::stod(expression.substr(i), &idx);
			tokens.push(value);
			output << value;

			i = i + idx - 1; //--i;
		}
		output << ' ';
	}

	while (!ops.empty())
	{
		auto top = ops.pop();
		tokens.push(operations.top()); operations.pop();
		output << top << ' ';
	}
	std::string ret = output.str();

	return { ret, tokens };
}

std::queue<OldToken> Parser::convertToOld() const
{
	std::queue<OldToken> ret;
	/*auto qtok = tokens;
	std::vector<OldToken> vtok(qtok.size());

	for (auto &t : vtok)
	{
		t = qtok.front();
		qtok.pop();
	}

	while (!vtok.empty())
	{
		auto current = vtok.back();
		auto &value = current.getValue();

		switch (current.getType())
		{
		case OldToken::Type::OPERAND:
		{
			auto num = std::any_cast<Operand>(value);
			ret.push(num);
		} break;
		case OldToken::Type::OPERATION:
		{
			auto oper = std::any_cast<OldOperation>(value);
			switch (oper.type)
			{
			case OldOperation::FUNCTION:
			{
				ret.push(static_cast<Functions>(oper.f));
			} break;
			case OldOperation::BINARY:
			{
				ret.push(static_cast<BinaryOPS>(oper.b));
			} break;
			case OldOperation::UNARY:
			{
				ret.push(static_cast<UnaryOPS>(oper.u));
			} break;
			default:
				break;
			}
		}
		}
		vtok.pop_back();
	}*/
	return ret;
}

//std::pair<std::string, std::queue<Token>> Parser::ShuntingYard(const std::string &expression)
//{
//	// 3 + 5 - (6 / 2)
//	// 3 5 + 6 2 / -
//
//	// Queue<std::shared_ptr<IToken>> tokens;
//	std::queue<OldToken> tokens;
//	Stack<std::underlying_type_t<operations::Functions>> ops;
//	Stack<OldOperation> uniops;
//	// Stack<Functions> fns;
//	std::ostringstream output;
//	std::string ret;
//
//	// experimental
//	std::queue<Token> vtokens;
//	std::stack<Operation> voperations;
//
//	for (std::string::size_type i = 0; i != expression.length(); ++i)
//	{
//		const std::string::value_type current = expression.at(i);
//		if (std::isspace(current)) continue;
//		else if (binops.find(static_cast<BinaryOPS>(current)) != binops.end())
//		{
//			BinaryOPS operation = static_cast<BinaryOPS>(current);
//			if (!ops.empty())
//			{
//				auto top = ops.top(); //o2
//				// if (auto fn = static_cast<Functions>(top); operations::funcs.find(fn) != funcs.end()) { tokens.push(fn); output << ' '; }
//				while (!ops.empty() && top != '(' && Precedence::checkPrecedence((BinaryOPS)top, (BinaryOPS)current)) {
//					auto o2 = ops.pop();
//					output << o2 << ' ';
//					tokens.push(uniops.pop());
//					vtokens.push(voperations.top()); voperations.pop();
//					top = ops.top();
//				}
//			}
//			ops.push(current); // o1
//			// OldOperation operation; operation.type = operations::Type::BINARY;
//			// uniops.push(std::move(OldOperation{ static_cast<BinaryOPS>(current) }));
//			uniops.push(static_cast<BinaryOPS>(current));
//			voperations.push(operation);
//		}
//		else if (std::isalpha(current)) // combine all chars until they are alphabets
//		{
//			// lets assume the first token after any alphabet is '(' sqrt(10.0678)
//			auto ite = std::find(expression.cbegin() + i, expression.cend(), ')'); // closing of function
//			std::string::size_type start = expression.find_first_of("(", i+2);
//			auto fn = expression.substr(i, start - i);
//			auto itb = expression.cbegin() + i; // std::advance unusable because const string : but std::next can be...
//
//			if (operations::funcids.find(fn) == funcids.end()) continue;
//			// if (operations::funcids.find(fn) != funcids.end())
//			OldOperation operation; operation.type = OldOperation::FUNCTION; operation.f = funcids.at(fn);
//			uniops.push(std::move(operation));
//			voperations.push(funcids.at(fn));
//			{
//				std::string whole(itb, ite); whole.push_back(')'); // for debugging purposes
//				Operand value = std::stod(whole.substr(fn.length() + 1));
//
//				auto tops = uniops.top();
//				tokens.push(value);
//				tokens.push(uniops.pop());
//
//				vtokens.push(value);
//				// vtokens.push(static_cast<operations::Functions>(tops.f));
//				vtokens.push(voperations.top()); voperations.pop(); // to be unlocked soon
//
//				output << value << ' ';
//				// output << fn << ' ';
//				output << (char)operations::funcids.at(fn);
//
//				// ops.push(operations::funcids.at(fn)); // wont work
//				i += whole.length() - 1;
//			}
//		}
//		else if (current == '(') ops.push('(');
//		else if (current == ')') // asserting whether operator stack is empty can indicate paren mismatch
//		{
//			decltype(ops)::value_type top;
//			if (ops.empty()) continue;
//			for (top = ops.pop(); top != '('; top = ops.pop())
//			{
//				if (ops.empty()) throw std::logic_error("Expression Mismatch");
//				output << ' ' << top;
//
//				auto tops = uniops.top();
//
//				/*switch (tops.type)
//				{
//				case OldOperation::Type::BINARY:
//					vtokens.push(static_cast<operations::BinaryOPS>(tops.b));
//					break;
//				case OldOperation::Type::UNARY:
//					vtokens.push(static_cast<operations::UnaryOPS>(tops.u));
//					break;
//				case OldOperation::Type::FUNCTION:
//					vtokens.push(static_cast<operations::Functions>(tops.f));
//					break;
//				default:
//					break;
//				}*/
//				vtokens.push(voperations.top()); voperations.pop(); // UNLOCK
//				tokens.push(uniops.pop());
//			}
//		}
//		else if (std::ispunct(current) && current == ','); // pop all operators from operator stack into queue (while its not left paren)
//		else if (std::isdigit(current) || current == '.')
//		{
//			std::size_t idx = 0;
//			Operand value = std::stod(expression.substr(i), &idx);
//			tokens.push({ value });
//			vtokens.push(value);
//			output << value;
//			i = i + idx - 1; //--i;
//		}
//		output << ' ';
//	}
//
//	while (!ops.empty())
//	{
//		auto top = ops.pop();
//	auto tops = uniops.top();
//	/*vtokens.push(([] (const auto &token) -> Token {
//		switch (token.type)
//		{
//		case OldOperation::Type::BINARY:
//			return static_cast<operations::BinaryOPS>(token.b);
//		case OldOperation::Type::UNARY:
//			return static_cast<operations::UnaryOPS>(token.u);
//		case OldOperation::Type::FUNCTION:
//			return static_cast<operations::Functions>(token.f);
//		default:
//			break;
//		}
//		return -888.888;
//		})(tops));*/
//		vtokens.push(voperations.top()); voperations.pop(); // UNLOCK
//		tokens.push(uniops.pop()); output << top << ' ';
//	}
//	ret = output.str();
//
//	return { ret, vtokens };
//}
