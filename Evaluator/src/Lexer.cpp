#include <algorithm>
#include "Lexer.hpp"

using namespace evaluator;
using namespace operations;

enum struct TokenType { OPERATION, OPERAND, FUNCTION, SYMBOL, PARENS, UNKNOWN };

Lexer::Lexer(std::string_view expr) : expression(expr), filled(!expression.empty())
{
}

void Lexer::set(std::string_view expr)
{
    expression = expr;
    filled = !expression.empty();
}

Lexer::TokenQueue&& Lexer::tokenize() const
{
    /*
     * std::string expression(this->expression.cbegin(),
     *             std::remove_if(this->expression.cbegin(), this->expression.cend(), isspace));
     */

    TokenType previous = TokenType::UNKNOWN;
    for(decltype(expression)::size_type i = 0; i < expression.length(); ++i)
    {
        decltype(expression)::value_type current = expression[i];

        if(std::isspace(current)) continue;
        else if(std::isdigit(current) || current == Symbols::PERIOD)
        {
            std::size_t idx = 0;
            auto num = expression.substr(i, expression.find_first_not_of(".0123456789", i) - i);
            Operand value = std::stod(num, &idx);
            tokens.push(value);
            previous = TokenType::OPERAND;

            i += idx - 1;
        }
        else if (
            operations::UnaryOPS operation = static_cast<UnaryOPS>(current);
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
            if(previous == TokenType::OPERATION || previous == TokenType::PARENS || i == 0) tokens.push(operation);
            else tokens.push(static_cast<BinaryOPS>(current));
            previous = TokenType::OPERATION;
        }
        else if (
            BinaryOPS operation = static_cast<BinaryOPS>(current);
            binops.find(operation) != binops.end()
        )
        {
            tokens.push(operation);
            previous = TokenType::OPERATION;
        }
        else if(std::isalpha(current))
        {
            auto ite = std::find(expression.cbegin() + i, expression.cend(), ')'); // closing of function
            std::string::size_type start = expression.find_first_of('(', i+2);
            auto fn = expression.substr(i, start - i);
            auto itb = expression.cbegin() + i;

            if (operations::funcids.find(fn) == funcids.end()) continue; // not a registered function (not found in registry map)
            tokens.push(funcids.at(fn));

            Operand value = std::stod(expression.substr(fn.length() + i + 1, std::distance(ite, std::next(itb, fn.length() + 1))));
            tokens.push(value);
            previous = TokenType::FUNCTION;

            i += std::distance(itb, ite);
        }
        else if(current == '(') { tokens.push(Symbols::LPAREN); previous = TokenType::PARENS; }
        else if(current == ')') { tokens.push(Symbols::RPAREN); previous = TokenType::PARENS; }
        else if(std::ispunct(current) && current == Symbols::COMMA) tokens.push(Symbols::COMMA);
        else; // UNKNOWN TOKEN ENCOUNTERED
    }
    return std::move(tokens);
}


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
