#include <algorithm>
#include <cctype>
#include <cassert>

#include "Lexer.hpp"

using namespace evaluator;
using namespace operations;

enum struct eTokenType { OPERATION, OPERAND, FUNCTION, SYMBOL, LPAREN, RPAREN, UNKNOWN };

Lexer::Lexer(std::string_view expr) : expression(expr), filled(!expression.empty())
{
}

void Lexer::set(std::string_view expr)
{
    expression = expr;
    filled = !expression.empty();
}

Lexer::TokenQueue& Lexer::tokenize() const
{
    /*
     * std::string expression(this->expression.cbegin(),
     *             std::remove_if(this->expression.cbegin(), this->expression.cend(), isspace));
     */
    auto &tokens = this->tokens;

    eTokenType previous = eTokenType::UNKNOWN;
    for(decltype(expression)::size_type i = 0; i < expression.length(); ++i)
    {
        decltype(expression)::value_type current = expression[i];

        if(std::isspace(current)) continue;
        else if(std::isdigit(current) || static_cast<Symbols>(current) == Symbols::PERIOD)
        {
            std::size_t idx = 0;
            auto num = expression.substr(i, expression.find_first_not_of(".0123456789eE+-", i) - i);
            // auto num = expression.substr(i);
            Operand value = std::stod(num, &idx);
            tokens.push(value);
            previous = eTokenType::OPERAND;

            i += idx - 1;
        }
        else if (
            UnaryOPS operation = static_cast<UnaryOPS>(current);
            unops.find(operation) != unops.end()
        )
        {
            /*
             * Check if it really is Unary operator
             * if the next token is a number but the second next is not
             * (either its the EOF or its something else i.e paren, operator)
             * if the previous token is an operator then this one is unary
            */
            /*
            decltype(expression)::value_type previous = i > 0 ? expression[i - 1] : 0;
            if(std::isspace(previous)) previous = i - 1 > 0 ? expression[i - 2] : 0;
            if(previous && (!std::isdigit(previous) || previous != Symbols::PERIOD))
                tokens.push(operation);
            else
                tokens.push(static_cast<BinaryOPS>(current));
            */
            if(previous == eTokenType::OPERATION || previous == eTokenType::LPAREN || i == 0) tokens.emplace(Operation{operation});
            else tokens.push(Operation{static_cast<BinaryOPS>(operation)});
            previous = eTokenType::OPERATION;
        }
        else if (
            BinaryOPS operation = static_cast<BinaryOPS>(current);
            binops.find(operation) != binops.end()
        )
        {
            tokens.emplace(Operation{operation});
            previous = eTokenType::OPERATION;
        }
        else if(std::isalpha(current))
        {
            auto ite = std::find(expression.cbegin() + i, expression.cend(), ')'); // closing of function
            std::string::size_type start = expression.find_first_of('(', i+2);
            auto fn = expression.substr(i, start - i);
            auto itb = expression.cbegin() + i;

            if (operations::funcids.find(fn) == funcids.end()) continue; // not a registered function (not found in registry map)
            tokens.emplace(Operation{funcids.at(fn)});

            Operand value = std::stod(expression.substr(fn.length() + i + 1, std::distance(ite, std::next(itb, fn.length() + 1))));
            tokens.push(value);
            previous = eTokenType::FUNCTION;

            i += std::distance(itb, ite);
        }
        else if(current == '(') { tokens.push(Symbols::LPAREN); previous = eTokenType::LPAREN; }
        else if(current == ')') { tokens.push(Symbols::RPAREN); previous = eTokenType::RPAREN; }
        else if(std::ispunct(current) && static_cast<Symbols>(current) == Symbols::COMMA) tokens.push(Symbols::COMMA);
        else; // UNKNOWN TOKEN ENCOUNTERED
    }
    return tokens;
}

Lexer::TokenQueue& Lexer::getTokens() const { return tokens; }


/*
    for(auto current : expression)
    {
        if(std::isspace(current)) continue;
        switch(current)
        {
            case
        }
    }
*/
