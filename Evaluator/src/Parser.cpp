#include <sstream>
#include <stack>
#include <cctype>

#include "common.h"
#include "Parser.hpp"
#include "Stack.hpp"

using namespace evaluator;
using namespace evaluator::operations;

Parser::Parser(std::string_view exp) : input(exp)
{
}

Parser& Parser::feed(std::string_view exp)
{
	input = exp;
	return *this;
}

Parser::TokenQueue&& Parser::parse()
{
    return ShuntingYard(this);
}

Parser::TokenQueue&& Parser::getTokens()
{
    return std::move(tokens);
}

Parser::TokenQueue&& Parser::ShuntingYard(Parser *const parser)
{
    // Finite State Machine : digits, symbols, letters, parenthesis
    auto &tokens = parser->tokens;
    const auto &expression = parser->input;
    VecStack<UnifiedToken> operations;
    // std::int_fast8_t parens = 0;

    for (std::string::size_type i = 0; i != expression.length(); ++i)
    {
        const std::string::value_type current = expression.at(i);
        if (std::isspace(current)) continue;
        else if (binops.find(static_cast<BinaryOPS>(current)) != binops.end())
        {
            BinaryOPS operation = static_cast<BinaryOPS>(current);
            if (!operations.empty())
            {
                auto top = operations.top();
                // problem to fix here : need some workaround to tell whether the top is not a parentheses (counter makes problem)
                while (!(std::holds_alternative<Symbols>(top) && std::get<Symbols>(top) == Symbols::PAREN)
                       &&  Precedence::checkPrecedence(std::get<BinaryOPS>(std::get<Operation>(top)), operation)) {
                    tokens.push(std::get<Operation>(operations.top())); operations.pop();
                    if(!operations.empty()) top = std::get<Operation>(operations.top());
                    else break;
                }
                //if(parens < 0) parens = 0;
            }
            operations.push(operation);
        }
        else if (std::isalpha(current)) // combine all chars until they are alphabets
        {
            // lets assume the first token after any alphabet is '(' sqrt(10.0678)
            auto ite = std::find(expression.cbegin() + i, expression.cend(), ')'); // closing of function
            std::string::size_type start = expression.find_first_of('(', i+2);
            auto fn = expression.substr(i, start - i);
            auto itb = expression.cbegin() + i;

            if (operations::funcids.find(fn) == funcids.end()) continue; // not a registered function (not found in registry map

            operations.push(funcids.at(fn));
            {
                std::string whole(itb, ite); whole.push_back(')'); // for debugging purposes
                Operand value = std::stod(whole.substr(fn.length() + 1));;

                tokens.push(value);
                tokens.push(std::get<Operation>(operations.top())); operations.pop();

                i += whole.length() - 1;
            }
        }
        else if (current == '(') operations.push(Symbols::PAREN);
        else if (current == ')') // asserting whether operator stack is empty can indicate paren mismatch
        {
            if (operations.empty()) continue;
            for(auto top = operations.top();
                 !(std::holds_alternative<Symbols>(top) && std::get<Symbols>(top) == Symbols::PAREN);
                top = operations.top(), operations.pop())
            {
                operations.pop();
                if (operations.empty()) throw std::logic_error("Expression Mismatch");
                tokens.push(std::get<Operation>(top));
            }
        }
        else if (std::ispunct(current) && current == ','); // pop all operators from operator stack into queue (while its not left paren)
        else if (std::isdigit(current) || current == '.')
        {
            std::size_t idx = 0;
            Operand value = std::stod(expression.substr(i), &idx);
            tokens.push(value);

            i = i + idx - 1; //--i;
        }
    }

    while (!operations.empty())
    {
        tokens.push(std::get<Operation>(operations.top()));
        operations.pop();
    }

    return std::move(tokens);
}
