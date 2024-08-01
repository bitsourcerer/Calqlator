#include <algorithm>
#include <cctype>
#include <cassert>
#include <cstdint>

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
    std::uint8_t func = 0; // to mark if currently processing function subexpr

    eTokenType previous = eTokenType::UNKNOWN;
    for(decltype(expression)::size_type i = 0; i < expression.length(); ++i)
    {
        decltype(expression)::value_type current = expression[i];

        if(std::isspace(current) || std::isblank(current)) continue;
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
            // auto itb = expression.cbegin() + i;
            // auto ite = std::find(expression.cbegin() + i, expression.cend(), ')'); // closing of function
            auto start = expression.find_first_of(static_cast<decltype(expression)::value_type>(Sentinels::FUNC_BEG), i+2);
            auto name = expression.substr(i, start - i);
            if(start == std::string::npos) name = expression.substr(
                    i, expression.find_first_of(
                        static_cast<decltype(expression)::value_type>(Sentinels::FUNC_END), i
                    ) - i
                ); // Parser will get it!

            if (operations::funcids.find(name) == funcids.end()) {
                std::string msg;
                start = expression.find_first_of("( )", i);
                name = expression.substr(i, start - i);

                if(func) {
                    msg = '\'' + name + "' is not a valid argument to function!";
                }
                else
                    msg = "name '" + name + "' is not registered!";
                throw except::lexer_error(msg); // not a registered function (not found in registry map)
            }
            ++func;
            tokens.emplace(Operation{funcids.at(name)});

            // i += std::distance(itb, ite);
            i += name.length() - 1;
            previous = eTokenType::FUNCTION;
        }
        else if(current == '(')
        {
            if(previous == eTokenType::FUNCTION && false) /* DISABLED */ {
                ++func;
                tokens.push(/*Sentinels::FUNC_BEG*/ Symbols::LPAREN);
            }
            else
                tokens.push(Symbols::LPAREN);
            previous = eTokenType::LPAREN;
        }
        else if(current == ')')
        {
            if(func) {
                tokens.push(/*Sentinels::FUNC_END*/ Symbols::RPAREN); // not yet activated
                --func;
            }
            else tokens.push(Symbols::RPAREN);
            previous = eTokenType::RPAREN;
        }
        else if(std::ispunct(current) && static_cast<Symbols>(current) == Symbols::COMMA) tokens.push(Symbols::COMMA);
        else {
            // tokens = TokenQueue(); // empty the tokens
            throw except::lexer_error("Unknown Token! " + std::string(1, current));
        } // UNKNOWN TOKEN ENCOUNTERED
    }
    return tokens;
}

Lexer::TokenQueue& Lexer::getTokens() const { return tokens; }

/*
void Lexer::clear() const
{
    if(!tokens.empty()) tokens = TokenQueue();
}
*/

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
